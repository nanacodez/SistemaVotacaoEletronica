#include "eleitor.h"
#include "modelos.h"
#include "utils.h"
#include "validacoes.h"
#include "database.h"

void cadastrarEleitor() {
    limparTela();
    printf("--- Cadastro de Eleitor ---\n");

    // Lógica de negócio agora usa a interface do banco
    if (db_getTotalEleitores() >= MAX_ELEITORES) {
        printf("!! ERRO: Limite de eleitores atingido (%d)!\n", MAX_ELEITORES);
        return;
    }

    char nome[TAM_NOME];
    char titulo[TAM_TITULO + 1];
    int idade;

    printf("Digite o nome completo: ");
    lerString(nome, TAM_NOME);
    if (!validarStringNaoVazia(nome)) return;

    printf("Digite a idade: ");
    scanf("%d", &idade);
    limparBufferEntrada();
    if (!validarIdade(idade)) return;

    printf("Digite o Titulo de Eleitor (%d digitos): ", TAM_TITULO);
    lerString(titulo, TAM_TITULO + 1);
    if (!validarTitulo(titulo)) return;

    Eleitor novoEleitor;
    strcpy(novoEleitor.nome, nome);
    strcpy(novoEleitor.tituloEleitor, titulo);
    novoEleitor.idade = idade;
    novoEleitor.jaVotou = false;

    // Adiciona ao "banco" através da função
    if (db_adicionarEleitor(novoEleitor)) {
        printf("\n>> SUCESSO: Eleitor '%s' cadastrado.\n", novoEleitor.nome);
    } else {
        printf("\n!! FALHA: Nao foi possivel cadastrar o eleitor.\n");
    }
    
    printf("Pressione Enter para continuar...");
    getchar();
}

void listarEleitores() {
    limparTela();
    int total = db_getTotalEleitores();
    printf("--- Lista de Eleitores Cadastrados (%d) ---\n", total);
    
    if (total == 0) {
        printf("Nenhum eleitor cadastrado.\n");
    } else {
        for (int i = 0; i < total; i++) {
            // Pega o eleitor do banco usando a função
            Eleitor* eleitor = db_getEleitorPorIndice(i);
            if (eleitor != NULL) {
                printf("[%d] Nome: %s | Titulo: %s | Idade: %d\n", 
                       i + 1, 
                       eleitor->nome, 
                       eleitor->tituloEleitor, 
                       eleitor->idade);
            }
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}
