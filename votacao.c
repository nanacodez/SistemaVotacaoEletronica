#include "votacao.h"
#include "config.h"
#include "utils.h"
#include "database.h"
#include "apuracao.h" // Inclui o novo módulo de apuração

// Função auxiliar interna para confirmar o voto
bool confirmarVoto(const char* mensagem) {
    char confirmacao;
    printf("%s (s/n): ", mensagem);
    scanf(" %c", &confirmacao);
    limparBufferEntrada();
    return (tolower(confirmacao) == 's');
}

void realizarVotacao() {
    limparTela();
    printf("==================================\n");
    printf("       MÓDULO DE VOTAÇÃO\n");
    printf("==================================\n");

    // --- 1. Autenticação do Eleitor ---
    char titulo[TAM_TITULO + 1];
    printf("Digite seu Titulo de Eleitor: ");
    lerString(titulo, TAM_TITULO + 1);

    Eleitor* eleitor = db_buscarEleitorPorTitulo(titulo);

    if (eleitor == NULL) {
        printf("\n!! ERRO: Eleitor nao cadastrado no sistema.\n");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    }

    if (eleitor->jaVotou) {
        printf("\n!! ATENCAO: O eleitor '%s' ja votou.\n", eleitor->nome);
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    }

    printf("\n>> Eleitor identificado: %s\n", eleitor->nome);
    printf("----------------------------------\n");

    // --- 2. Lógica de Voto ---
    char voto[TAM_NUM_CANDIDATO + 1];
    printf("Digite o numero do seu candidato (%d digitos)\n", TAM_NUM_CANDIDATO);
    printf("Ou digite 'BRANCO' para votar em branco: ");
    lerString(voto, sizeof(voto));

    // Voto em Branco
    if (strcmp(voto, "BRANCO") == 0) {
        if (confirmarVoto("Confirmar voto EM BRANCO?")) {
            registrarVotoBranco();
            eleitor->jaVotou = true;
            printf("\n>> Voto EM BRANCO registrado com sucesso!\n");
        } else {
            printf("\n>> Votacao cancelada.\n");
        }
    } 
    // Voto em Candidato (Válido ou Nulo)
    else {
        Candidato* candidato = db_buscarCandidatoPorNumero(voto);

        // Voto Nulo (Candidato não existe)
        if (candidato == NULL) {
            printf("\n!! Numero de candidato invalido.\n");
            if (confirmarVoto("Confirmar voto NULO?")) {
                registrarVotoNulo();
                eleitor->jaVotou = true;
                printf("\n>> Voto NULO registrado com sucesso!\n");
            } else {
                printf("\n>> Votacao cancelada.\n");
            }
        } 
        // Voto Válido
        else {
            printf("\n--- Voce esta votando em: ---\n");
            printf("Nome: %s\n", candidato->nome);
            printf("Partido: %s\n", candidato->partido);
            printf("----------------------------------\n");
            
            if (confirmarVoto("Confirmar voto neste candidato?")) {
                candidato->votosRecebidos++; // A "integração" acontece aqui!
                eleitor->jaVotou = true;
                printf("\n>> Voto VALIDO registrado com sucesso!\n");
            } else {
                printf("\n>> Votacao cancelada.\n");
            }
        }
    }

    printf("Pressione Enter para sair da cabine...");
    getchar();
}