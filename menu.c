#include "menu.h"
#include "utils.h"
#include "database.h"   // Para mostrar os totais
#include "eleitor.h"    // Para chamar as funções de eleitor
#include "candidato.h"  // Para chamar as funções de candidato

int exibirMenuPrincipal() {
    int escolha = -1;
    
    limparTela();
    printf("==================================\n");
    printf("  SISTEMA DE VOTAÇÃO ELETRÔNICA\n");
    printf("        MODULO DE CADASTRO\n");
    printf("==================================\n");
    printf("Eleitores cadastrados: %d\n", db_getTotalEleitores());
    printf("Candidatos cadastrados: %d\n", db_getTotalCandidatos());
    printf("----------------------------------\n");
    printf("1. Cadastrar Eleitor\n");
    printf("2. Cadastrar Candidato\n");
    printf("3. Listar Eleitores\n");
    printf("4. Listar Candidatos\n");
    printf("0. Sair\n");
    printf("==================================\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &escolha);
    limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf
    
    return escolha;
}

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
        case 0:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opcao invalida! Pressione Enter para tentar novamente.\n");
            getchar();
            break;
    }
}