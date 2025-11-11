/*
 * ===================================================================
 * ARQUIVO: menu.c
 * DESCRIÇÃO: Implementação do menu.
 * ===================================================================
 */

#include "menu.h"
#include "utils.h"
#include "database.h"
#include "eleitor.h"
#include "candidato.h"
#include "votacao.h"
#include "apuracao.h"

int exibirMenuPrincipal() {
    int escolha = -1;
    
    limparTela();
    printf("==================================\n");
    printf("  SISTEMA DE VOTAÇÃO ELETRÔNICA\n");
    printf("==================================\n");
    printf("Eleitores cadastrados: %d\n", db_getTotalEleitores());
    printf("Candidatos cadastrados: %d\n", db_getTotalCandidatos());
    printf("----------------------------------\n");
    printf("    FASE 1: CADASTRO\n");
    printf("1. Cadastrar Eleitor\n");
    printf("2. Cadastrar Candidato\n");
    printf("3. Listar Eleitores\n");
    printf("4. Listar Candidatos\n");
    printf("----------------------------------\n");
    printf("    FASE 2: VOTAÇÃO\n");
    printf("5. Realizar Votacao\n");
    printf("----------------------------------\n");
    printf("    FASE 3: APURAÇÃO\n");
    printf("6. Apurar e Exibir Resultados\n");
    printf("----------------------------------\n");
    printf("0. Sair\n");
    printf("==================================\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &escolha);
    limparBufferEntrada();
    
    return escolha;
}

// ESTA FUNÇÃO SÓ DEVE ESTAR AQUI!
void processarEscolha(int escolha) {
    switch (escolha) {
        case 1:
            cadastrarEleitor();
            break;
        case 2:
            cadastrarCandidato();
            break;
        case 3:
            listarEleitores();
            break;
        case 4:
            listarCandidatos();
            break;
        case 5:
            realizarVotacao();
            break;
        case 6:
            exibirResultados();
            break;
        case 0:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opcao invalida! Pressione Enter para tentar novamente.\n");
            getchar();
            break;
    }
}