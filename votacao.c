// correcao da implementacao da logica de voto

#include "votacao.h"
#include "config.h"
#include "utils.h"
#include "database.h"
#include "apuracao.h" // inclui o novo modulo de apuracao

// funcao auxiliar interna para confirmar o voto
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

    // autenticacao de eleitor
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

    // logica de voto
    
    bool votoConfirmado = false;
    while (!votoConfirmado) { // o loop continua ate um voto ser finalizado

        // logica de voto
        // buffer maior (TAM_NOME) para garantir que "BRANCO" caiba
        char bufferVoto[TAM_NOME]; 
        
        printf("\nDigite o numero do seu candidato (%d digitos)\n", TAM_NUM_CANDIDATO);
        printf("Ou digite 'BRANCO' para votar em branco: ");
        
        // agora o programa vai esperar aqui por conta do utils.c
        lerString(bufferVoto, sizeof(bufferVoto));

        // voto em branco
        if (strcmp(bufferVoto, "BRANCO") == 0) {
            if (confirmarVoto("Confirmar voto EM BRANCO?")) {
                registrarVotoBranco();
                eleitor->jaVotou = true;
                printf("\n>> Voto EM BRANCO registrado com sucesso!\n");
                votoConfirmado = true; // sai do loop
            } else {
                printf("\n>> Voto cancelado. Digite novamente.\n");
                // continua no loop
            }
        } 
        // voto em candidato (valido ou nulo)
        else {
            Candidato* candidato = db_buscarCandidatoPorNumero(bufferVoto);

            // voto nulo (candidato nao existe)
            if (candidato == NULL) {
                printf("\n!! Numero de candidato invalido.\n");
                if (confirmarVoto("Confirmar voto NULO?")) {
                    registrarVotoNulo();
                    eleitor->jaVotou = true;
                    printf("\n>> Voto NULO registrado com sucesso!\n");
                    votoConfirmado = true; // sai do loop
                } else {
                    printf("\n>> Voto cancelado. Digite novamente.\n");
                    // vontinua no loop
                }
            } 
            // voto Valido
            else {
                printf("\n--- Voce esta votando em: ---\n");
                printf("Nome: %s\n", candidato->nome);
                printf("Partido: %s\n", candidato->partido);
                printf("----------------------------------\n");
                
                if (confirmarVoto("Confirmar voto neste candidato?")) {
                    candidato->votosRecebidos++;
                    eleitor->jaVotou = true;
                    printf("\n>> Voto VALIDO registrado com sucesso!\n");
                    votoConfirmado = true; // sai do loop
                } else {
                    printf("\n>> Voto cancelado. Digite novamente.\n");
                    // continua no loop
                }
            }
        }
    } // fim do loop while 

    printf("\nPressione Enter para sair da cabine...");
    getchar();
}