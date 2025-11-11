#include "apuracao.h"
#include "config.h"
#include "utils.h"
#include "database.h"
#include "modelos.h" // Para usar a struct Candidato

// Contadores de votos não-nominais.
// São 'static' para serem privados deste módulo.
static int totalVotosNulos = 0;
static int totalVotosBrancos = 0;

void registrarVotoNulo() {
    totalVotosNulos++;
}

void registrarVotoBranco() {
    totalVotosBrancos++;
}

// --- Lógica de Ordenação (Bubble Sort) ---

// Função auxiliar para trocar dois candidatos de posição
void trocarCandidatos(Candidato* a, Candidato* b) {
    Candidato temp = *a;
    *a = *b;
    *b = temp;
}

// Ordena um array de candidatos do mais votado para o menos votado
void ordenarCandidatosPorVotos(Candidato array[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            // Compara o próximo com o atual
            if (array[j].votosRecebidos < array[j + 1].votosRecebidos) {
                trocarCandidatos(&array[j], &array[j + 1]);
            }
        }
    }
}

// --- Lógica de Apuração ---

void exibirResultados() {
    limparTela();
    printf("==================================\n");
    printf("     APURAÇÃO E RESULTADOS\n");
    printf("==================================\n");

    int totalCandidatos = db_getTotalCandidatos();
    if (totalCandidatos == 0) {
        printf("Nenhum candidato foi cadastrado.\n");
    }

    // 1. Copiar dados para um array local para poder ordenar
    // (NÃO queremos ordenar o banco de dados original)
    Candidato resultados[MAX_CANDIDATOS];
    int totalVotosValidos = 0;
    
    for (int i = 0; i < totalCandidatos; i++) {
        resultados[i] = *db_getCandidatoPorIndice(i); // Copia a struct
        totalVotosValidos += resultados[i].votosRecebidos;
    }

    // 2. Ordenar o array local
    ordenarCandidatosPorVotos(resultados, totalCandidatos);

    // 3. Exibir resultados ordenados
    printf("--- Votos Válidos (Mais votados) ---\n");
    for (int i = 0; i < totalCandidatos; i++) {
        printf("%d. %s (%s) - %d votos\n",
            i + 1,
            resultados[i].nome,
            resultados[i].partido,
            resultados[i].votosRecebidos);
    }

    // 4. Exibir outros votos
    printf("\n--- Outros Votos ---\n");
    printf("Votos em Branco: %d\n", totalVotosBrancos);
    printf("Votos Nulos: %d\n", totalVotosNulos);

    // 5. Correção e Integridade Final
    int totalEleitores = db_getTotalEleitores();
    int eleitoresQueVotaram = 0;
    for (int i = 0; i < totalEleitores; i++) {
        if (db_getEleitorPorIndice(i)->jaVotou) {
            eleitoresQueVotaram++;
        }
    }
    
    int totalVotosNaUrna = totalVotosValidos + totalVotosBrancos + totalVotosNulos;

    printf("\n--- Auditoria e Integridade ---\n");
    printf("Total de eleitores que votaram: %d\n", eleitoresQueVotaram);
    printf("Total de votos na urna: %d\n", totalVotosNaUrna);

    if (eleitoresQueVotaram == totalVotosNaUrna) {
        printf(">> SUCESSO: A contagem de votos bate com o numero de votantes.\n");
    } else {
        printf("!! FALHA DE INTEGRIDADE: Contagem de votos (%d) e votantes (%d) DIVERGENTE!\n",
            totalVotosNaUrna, eleitoresQueVotaram);
    }
    
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}