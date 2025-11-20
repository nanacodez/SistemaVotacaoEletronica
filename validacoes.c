#include "validacoes.h"
#include "database.h" // necessario para checar unicidade

bool stringContemApenasDigitos(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool validarIdade(int idade) {
    if (idade < IDADE_MINIMA_VOTAR) {
        printf("!! ERRO: Idade minima para votar e %d anos.\n", IDADE_MINIMA_VOTAR);
        return false;
    }
    return true;
}

bool validarTitulo(const char* titulo) {
    if (strlen(titulo) != TAM_TITULO) {
        printf("!! ERRO: O titulo deve ter exatamente %d digitos.\n", TAM_TITULO);
        return false;
    }
    if (!stringContemApenasDigitos(titulo)) {
        printf("!! ERRO: O titulo deve conter apenas numeros.\n");
        return false;
    }
    
    // funcao do banco de dados
    if (db_buscarEleitorPorTitulo(titulo) != NULL) {
        printf("!! ERRO: Este titulo de eleitor ja esta cadastrado.\n");
        return false;
    }
    
    return true;
}

bool validarNumeroCandidato(const char* numero) {
    if (strlen(numero) != TAM_NUM_CANDIDATO) {
        printf("!! ERRO: O numero do candidato deve ter %d digitos.\n", TAM_NUM_CANDIDATO);
        return false;
    }
    if (!stringContemApenasDigitos(numero)) {
        printf("!! ERRO: O numero deve conter apenas digitos.\n");
        return false;
    }

    if (db_buscarCandidatoPorNumero(numero) != NULL) {
        printf("!! ERRO: Este numero de candidato ja esta cadastrado.\a\n");
        return false;
    }
    
    return true;
}

bool validarStringNaoVazia(const char* str) {
    if (strlen(str) == 0) {
        printf("!! ERRO: Este campo nao pode ser vazio.\n");
        return false;
    }
    return true;
}