#ifndef MODELOS_H
#define MODELOS_H

#include "config.h"

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

#endif // MODELOS_H

