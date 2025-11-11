#include <stdio.h>      // Para entrada e saída (printf, scanf)
#include <stdlib.h>     // Para system("cls") e exit()
#include <string.h>     // Para manipulação de strings (strcpy, strcmp, strlen)
#include <ctype.h>      // Para validação de caracteres (isdigit)
#include <stdbool.h>    // Para usar 'true' e 'false'

// --- 1. HEADERS E CONSTANTES ---

// Limites do nosso banco de dados simulado
#define MAX_ELEITORES 1000
#define MAX_CANDIDATOS 50

// Regras de negócio para validação
#define TAM_TITULO 12
#define TAM_NUM_CANDIDATO 5 // Ex: 5 dígitos para Deputado Federal
#define IDADE_MINIMA_VOTAR 16

// Tamanhos dos campos de string (incluindo o caractere nulo '\0')
#define TAM_NOME 101
#define TAM_PARTIDO 51

/*
 * =========================================
 * 2. FORMATAÇÃO DE INFORMAÇÕES (STRUCTS)
 * =========================================
 */

typedef struct {
    char nome[TAM_NOME];
    char tituloEleitor[TAM_TITULO + 1]; // +1 para o '\0'
    int idade;
    bool jaVotou; // Essencial para a lógica de votação
} Eleitor;

typedef struct {
    char nome[TAM_NOME];
    char partido[TAM_PARTIDO];
    char numero[TAM_NUM_CANDIDATO + 1]; // +1 para o '\0'
    int votosRecebidos;
} Candidato;

/*
 * =========================================
 * 3. BANCO DE DADOS (SIMULADO)
 * =========================================
 * Usamos arrays globais e contadores para simplicidade.
 */

Eleitor db_eleitores[MAX_ELEITORES];
Candidato db_candidatos[MAX_CANDIDATOS];

int totalEleitores = 0;
int totalCandidatos = 0;


/*
 * =========================================
 * 6. FUNÇÕES UTILITÁRIAS
 * =========================================
 */

// Limpa o buffer de entrada (essencial após usar scanf)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Uma função segura para ler strings, evitando estouro de buffer
// e removendo o '\n' que o fgets deixa.
void lerString(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        // Remove a nova linha (newline) do final, se existir
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

// Verifica se uma string contém apenas dígitos
bool stringContemApenasDigitos(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// Limpa a tela (multi-plataforma)
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


/*
 * =========================================
 * 4. FUNÇÕES DE VALIDAÇÃO DE DADOS
 * =========================================
 */

// Valida se a idade é permitida
bool validarIdade(int idade) {
    if (idade < IDADE_MINIMA_VOTAR) {
        printf("!! ERRO: Idade minima para votar e %d anos.\n", IDADE_MINIMA_VOTAR);
        return false;
    }
    return true;
}

// Valida o formato e a unicidade do Título de Eleitor
bool validarTitulo(const char* titulo) {
    // 1. Valida o tamanho
    if (strlen(titulo) != TAM_TITULO) {
        printf("!! ERRO: O titulo deve ter exatamente %d digitos.\n", TAM_TITULO);
        return false;
    }

    // 2. Valida se são apenas dígitos
    if (!stringContemApenasDigitos(titulo)) {
        printf("!! ERRO: O titulo deve conter apenas numeros.\n");
        return false;
    }

    // 3. Valida unicidade (se já existe no "banco")
    for (int i = 0; i < totalEleitores; i++) {
        if (strcmp(db_eleitores[i].tituloEleitor, titulo) == 0) {
            printf("!! ERRO: Este titulo de eleitor ja esta cadastrado.\n");
            return false;
        }
    }
    
    return true;
}

// Valida o formato e a unicidade do Número do Candidato
bool validarNumeroCandidato(const char* numero) {
    // 1. Valida o tamanho
    if (strlen(numero) != TAM_NUM_CANDIDATO) {
        printf("!! ERRO: O numero do candidato deve ter %d digitos.\n", TAM_NUM_CANDIDATO);
        return false;
    }

    // 2. Valida se são apenas dígitos
    if (!stringContemApenasDigitos(numero)) {
        printf("!! ERRO: O numero deve conter apenas digitos.\n");
        return false;
    }

    // 3. Valida unicidade
    for (int i = 0; i < totalCandidatos; i++) {
        if (strcmp(db_candidatos[i].numero, numero) == 0) {
            printf("!! ERRO: Este numero de candidato ja esta cadastrado.\a\n");
            return false;
        }
    }
    
    return true;
}

// Valida se strings obrigatórias não estão vazias
bool validarStringNaoVazia(const char* str) {
    if (strlen(str) == 0) {
        printf("!! ERRO: Este campo nao pode ser vazio.\n");
        return false;
    }
    return true;
}


/*
 * =========================================
 * 5. FUNÇÕES DE CADASTRO (ENTRADA + VALIDAÇÃO)
 * =========================================
 */

void cadastrarEleitor() {
    limparTela();
    printf("--- Cadastro de Eleitor ---\n");

    // Verifica se há espaço no "banco de dados"
    if (totalEleitores >= MAX_ELEITORES) {
        printf("!! ERRO: Limite de eleitores atingido (%d)!\n", MAX_ELEITORES);
        return;
    }

    // Variáveis temporárias para coletar e validar os dados
    char nome[TAM_NOME];
    char titulo[TAM_TITULO + 1];
    int idade;

    // --- ENTRADA E VALIDAÇÃO ---

    // NOME
    printf("Digite o nome completo: ");
    lerString(nome, TAM_NOME);
    if (!validarStringNaoVazia(nome)) return;

    // IDADE
    printf("Digite a idade: ");
    scanf("%d", &idade);
    limparBufferEntrada();
    if (!validarIdade(idade)) return;

    // TÍTULO
    printf("Digite o Titulo de Eleitor (%d digitos): ", TAM_TITULO);
    lerString(titulo, TAM_TITULO + 1);
    if (!validarTitulo(titulo)) return;

    // --- SUCESSO NA VALIDAÇÃO ---
    // Copia os dados validados para a estrutura final no "banco"
    
    Eleitor novoEleitor;
    strcpy(novoEleitor.nome, nome);
    strcpy(novoEleitor.tituloEleitor, titulo);
    novoEleitor.idade = idade;
    novoEleitor.jaVotou = false; // Valor padrão

    // Adiciona ao "banco"
    db_eleitores[totalEleitores] = novoEleitor;
    totalEleitores++;

    printf("\n>> SUCESSO: Eleitor '%s' cadastrado.\n", novoEleitor.nome);
    printf("Pressione Enter para continuar...");
    getchar();
}

void cadastrarCandidato() {
    limparTela();
    printf("--- Cadastro de Candidato ---\n");

    if (totalCandidatos >= MAX_CANDIDATOS) {
        printf("!! ERRO: Limite de candidatos atingido (%d)!\n", MAX_CANDIDATOS);
        return;
    }
    
    char nome[TAM_NOME];
    char partido[TAM_PARTIDO];
    char numero[TAM_NUM_CANDIDATO + 1];

    // --- ENTRADA E VALIDAÇÃO ---
    
    // NOME
    printf("Digite o nome de urna do candidato: ");
    lerString(nome, TAM_NOME);
    if (!validarStringNaoVazia(nome)) return;
    
    // PARTIDO
    printf("Digite o partido (ex: PART): ");
    lerString(partido, TAM_PARTIDO);
    if (!validarStringNaoVazia(partido)) return;
    
    // NÚMERO
    printf("Digite o numero do candidato (%d digitos): ", TAM_NUM_CANDIDATO);
    lerString(numero, TAM_NUM_CANDIDATO + 1);
    if (!validarNumeroCandidato(numero)) return;
    
    // --- SUCESSO NA VALIDAÇÃO ---
    
    Candidato novoCandidato;
    strcpy(novoCandidato.nome, nome);
    strcpy(novoCandidato.partido, partido);
    strcpy(novoCandidato.numero, numero);
    novoCandidato.votosRecebidos = 0; // Valor padrão
    
    // Adiciona ao "banco"
    db_candidatos[totalCandidatos] = novoCandidato;
    totalCandidatos++;
    
    printf("\n>> SUCESSO: Candidato '%s (%s)' cadastrado com o numero %s.\n", novoCandidato.nome, novoCandidato.partido, novoCandidato.numero);
    printf("Pressione Enter para continuar...");
    getchar();
}

// Funções de listagem para verificar os dados
void listarEleitores() {
    limparTela();
    printf("--- Lista de Eleitores Cadastrados (%d) ---\n", totalEleitores);
    if (totalEleitores == 0) {
        printf("Nenhum eleitor cadastrado.\n");
    } else {
        for (int i = 0; i < totalEleitores; i++) {
            printf("[%d] Nome: %s | Titulo: %s | Idade: %d\n", 
                   i + 1, 
                   db_eleitores[i].nome, 
                   db_eleitores[i].tituloEleitor, 
                   db_eleitores[i].idade);
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarCandidatos() {
    limparTela();
    printf("--- Lista de Candidatos Cadastrados (%d) ---\n", totalCandidatos);
    if (totalCandidatos == 0) {
        printf("Nenhum candidato cadastrado.\n");
    } else {
        for (int i = 0; i < totalCandidatos; i++) {
            printf("[%d] Numero: %s | Nome: %s | Partido: %s\n", 
                   i + 1, 
                   db_candidatos[i].numero, 
                   db_candidatos[i].nome, 
                   db_candidatos[i].partido);
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}


/*
 * =========================================
 * 7. FUNÇÃO MAIN (MENU PRINCIPAL)
 * =========================================
 */

int main() {
    int escolha = -1;

    do {
        limparTela();
        printf("==================================\n");
        printf("  SISTEMA DE VOTAÇÃO ELETRÔNICA\n");
        printf("        MODULO DE CADASTRO\n");
        printf("==================================\n");
        printf("Eleitores cadastrados: %d\n", totalEleitores);
        printf("Candidatos cadastrados: %d\n", totalCandidatos);
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

        if (escolha == 1) {
            cadastrarEleitor();
        } 
        else if (escolha == 2) {
            cadastrarCandidato();
        } 
        else if (escolha == 3) {
            listarEleitores();
        } 
        else if (escolha == 4) {
            listarCandidatos();
        } 
        else if (escolha == 0) {
            printf("Saindo do sistema...\n");
        } 
        else {
            // Este 'else' final equivale ao 'default' do switch
            printf("Opcao invalida! Pressione Enter para tentar novamente.\n");
            getchar();
        }

    } while (escolha != 0);

    return 0;
}