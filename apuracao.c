#include "apuracao.h"
#include "config.h"
#include "utils.h"
#include "database.h"
#include "modelos.h" // para usar a struct candidato

// contadores de votos nao nominais
static int totalVotosNulos = 0;
static int totalVotosBrancos = 0;

void registrarVotoNulo() {
    totalVotosNulos++;
}

void registrarVotoBranco() {
    totalVotosBrancos++;
}

// logica de ordenacao

// funcao auxiliar para trocar dois candidatos de posicao
void trocarCandidatos(Candidato* a, Candidato* b) {
    Candidato temp = *a;
    *a = *b;
    *b = temp;
}

// ordena uma array de candidatos do mais votado para o menos votado
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

// logica de apuracao

void exibirResultados() {
    limparTela();
    printf("==================================\n");
    printf("     APURAÇÃO E RESULTADOS\n");
    printf("==================================\n");

    int totalCandidatos = db_getTotalCandidatos();
    if (totalCandidatos == 0) {
        printf("Nenhum candidato foi cadastrado.\n");
    }

    // copiar dados para um array local para poder ordenar
    Candidato resultados[MAX_CANDIDATOS];
    int totalVotosValidos = 0;
    
    for (int i = 0; i < totalCandidatos; i++) {
        resultados[i] = *db_getCandidatoPorIndice(i); // copia a struct
        totalVotosValidos += resultados[i].votosRecebidos;
    }

    // ordenar o array local
    ordenarCandidatosPorVotos(resultados, totalCandidatos);

    // exibir resultados ordenados
    printf("--- Votos Válidos (Mais votados) ---\n");
    for (int i = 0; i < totalCandidatos; i++) {
        printf("%d. %s (%s) - %d votos\n",
            i + 1,
            resultados[i].nome,
            resultados[i].partido,
            resultados[i].votosRecebidos);
    }

    // exibir outros votos
    printf("\n--- Outros Votos ---\n");
    printf("Votos em Branco: %d\n", totalVotosBrancos);
    printf("Votos Nulos: %d\n", totalVotosNulos);

    // correcao e integridade final
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