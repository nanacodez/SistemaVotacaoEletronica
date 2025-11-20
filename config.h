#ifndef CONFIG_H
#define CONFIG_H

// bibliotecas padrao 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// headers e constantes

// limites do nosso banco de dados simulado
#define MAX_ELEITORES 1000
#define MAX_CANDIDATOS 50

// regras de negocio para validacao
#define TAM_TITULO 12
#define TAM_NUM_CANDIDATO 5 // ex 5 digitos para deputado federal
#define IDADE_MINIMA_VOTAR 16

// tamanhos dos campos de string (incluindo o caractere nulo '\0')
#define TAM_NOME 101
#define TAM_PARTIDO 51

#endif // CONFIG_H

