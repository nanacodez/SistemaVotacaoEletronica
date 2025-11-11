#ifndef VALIDACOES_H
#define VALIDACOES_H

#include "config.h"

// Verifica se uma string contém apenas dígitos
bool stringContemApenasDigitos(const char* str);

// Valida se a idade é permitida
bool validarIdade(int idade);

// Valida o formato e a unicidade do Título de Eleitor
bool validarTitulo(const char* titulo);

// Valida o formato e a unicidade do Número do Candidato
bool validarNumeroCandidato(const char* numero);

// Valida se strings obrigatórias não estão vazias
bool validarStringNaoVazia(const char* str);

#endif // VALIDACOES_H