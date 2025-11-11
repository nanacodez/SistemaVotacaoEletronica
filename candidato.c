#include "candidato.h"
#include "modelos.h"
#include "utils.h"
#include "validacoes.h"
#include "database.h"

void cadastrarCandidato() {
    limparTela();
    printf("--- Cadastro de Candidato ---\n");

    if (db_getTotalCandidatos() >= MAX_CANDIDATOS) {
        printf("!! ERRO: Limite de candidatos atingido (%d)!\n", MAX_CANDIDATOS);
        return;
    }
    
    char nome[TAM_NOME];
    char partido[TAM_PARTIDO];
    char numero[TAM_NUM_CANDIDATO + 1];

    printf("Digite o nome de urna do candidato: ");
    lerString(nome, TAM_NOME);
    if (!validarStringNaoVazia(nome)) return;
    
    printf("Digite o partido (ex: PART): ");
    lerString(partido, TAM_PARTIDO);
    if (!validarStringNaoVazia(partido)) return;
    
    printf("Digite o numero do candidato (%d digitos): ", TAM_NUM_CANDIDATO);
    lerString(numero, TAM_NUM_CANDIDATO + 1);
    if (!validarNumeroCandidato(numero)) return;
    
    Candidato novoCandidato;
    strcpy(novoCandidato.nome, nome);
    strcpy(novoCandidato.partido, partido);
    strcpy(novoCandidato.numero, numero);
    novoCandidato.votosRecebidos = 0;
    
    if (db_adicionarCandidato(novoCandidato)) {
        printf("\n>> SUCESSO: Candidato '%s (%s)' cadastrado com o numero %s.\n", novoCandidato.nome, novoCandidato.partido, novoCandidato.numero);
    } else {
        printf("\n!! FALHA: Nao foi possivel cadastrar o candidato.\n");
    }
    
    printf("Pressione Enter para continuar...");
    getchar();
}

void listarCandidatos() {
    limparTela();
    int total = db_getTotalCandidatos();
    printf("--- Lista de Candidatos Cadastrados (%d) ---\n", total);
    
    if (total == 0) {
        printf("Nenhum candidato cadastrado.\n");
    } else {
        for (int i = 0; i < total; i++) {
            Candidato* candidato = db_getCandidatoPorIndice(i);
            if (candidato != NULL) {
                printf("[%d] Numero: %s | Nome: %s | Partido: %s\n", 
                       i + 1, 
                       candidato->numero, 
                       candidato->nome, 
                       candidato->partido);
            }
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}