#ifndef CONFIG_H
#define CONFIG_H

// --- Bibliotecas Padrao ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

#endif // CONFIG_H

