#include "candidato.h"
#include "modelos.h"
#include "utils.h"
#include "validacoes.h"
#include "database.h"

// funcao para cadastrar um novo candidato no sistema
void cadastrarCandidato() {
    limparTela(); // limpa a tela do terminal para melhor apresentacao
    printf("--- Cadastro de Candidato ---\n");

    // verifica se o limite maximo de candidatos ja foi atingido
    if (db_getTotalCandidatos() >= MAX_CANDIDATOS) {
        printf("!! ERRO: Limite de candidatos atingido (%d)!\n", MAX_CANDIDATOS);
        return;
    }
    
    // declaracao dos buffers para armazenar a entrada do usuario
    char nome[TAM_NOME];
    char partido[TAM_PARTIDO];
    char numero[TAM_NUM_CANDIDATO + 1];

    // leitura e validacao do nome
    printf("Digite o nome de urna do candidato: ");
    lerString(nome, TAM_NOME);
    if (!validarStringNaoVazia(nome)) return;

    // leitura e validacao do partido
    printf("Digite o partido (ex: PART): ");
    lerString(partido, TAM_PARTIDO);
    if (!validarStringNaoVazia(partido)) return;

    // leitura e validacao do numero
    printf("Digite o numero do candidato (%d digitos): ", TAM_NUM_CANDIDATO);
    lerString(numero, TAM_NUM_CANDIDATO + 1);

    // valida se o numero tem o formato e tamanho corretos, esta funcao tambem deve verificar a unicidade
    if (!validarNumeroCandidato(numero)) return;
    
    // cria uma nova estrutura candidato
    Candidato novoCandidato;

    // copia os dados de entrada para a estrutura
    strcpy(novoCandidato.nome, nome);
    strcpy(novoCandidato.partido, partido);
    strcpy(novoCandidato.numero, numero);
    novoCandidato.votosRecebidos = 0; // inicializa a contagem de votos
    
    // tenta adicionar o novo candidato ao banco de dados (array/lista)
    if (db_adicionarCandidato(novoCandidato)) {
        // mensagem de sucesso
        printf("\n>> SUCESSO: Candidato '%s (%s)' cadastrado com o numero %s.\n", novoCandidato.nome, novoCandidato.partido, novoCandidato.numero);
    } else {

        // mensagem de falha
        printf("\n!! FALHA: Nao foi possivel cadastrar o candidato.\n");
    }
    
    printf("Pressione Enter para continuar...");
    getchar(); // pausa a execucao ate o usuario pressionar enter
}

// funcao para listar todos os candidatos cadastrados
void listarCandidatos() {
    limparTela(); // limpa a tela
    int total = db_getTotalCandidatos(); // obtem o numero total de candidatos
    printf("--- Lista de Candidatos Cadastrados (%d) ---\n", total);
    
    // verifica se ha candidatos para listar
    if (total == 0) {
        printf("Nenhum candidato cadastrado.\n");
    } else {
        // loop para iterar sobre todos os candidatos
        for (int i = 0; i < total; i++) {
            // obtem um ponteiro para o candidato na posicao 'i'
            Candidato* candidato = db_getCandidatoPorIndice(i);
            // verifica se o ponteiro e valido antes de acessar os dados
            if (candidato != NULL) {
                // imprime as informacoes do candidato
                printf("[%d] Numero: %s | Nome: %s | Partido: %s\n", 
                       i + 1, // mostra a contagem iniciando em 1
                       candidato->numero, // acesso aos membros da estrutura atraves do ponteiro
                       candidato->nome, 
                       candidato->partido);
            }
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar(); // pausa a execucao
}