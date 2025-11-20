#ifndef VALIDACOES_H
#define VALIDACOES_H

#include "config.h"

// verifica se uma string contem apenas digitos
bool stringContemApenasDigitos(const char* str);

// valida se a idade eh permitida
bool validarIdade(int idade);

// valida o formato e a unicidade do titulo de eleitor
bool validarTitulo(const char* titulo);

// valida o formato e a unicidade do numero do candidato
bool validarNumeroCandidato(const char* numero);

// valida se strings obrigatorias nao estao vazias
bool validarStringNaoVazia(const char* str);

#endif // VALIDACOES_H