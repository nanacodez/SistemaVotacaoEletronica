#ifndef DATABASE_H
#define DATABASE_H

#include "modelos.h"

// --- Getters de Contagem ---
int db_getTotalEleitores();
int db_getTotalCandidatos();

// --- Getters de Objetos ---
Eleitor* db_getEleitorPorIndice(int indice);
Candidato* db_getCandidatoPorIndice(int indice);

// --- Funções de Busca (para validação) ---
Eleitor* db_buscarEleitorPorTitulo(const char* titulo);
Candidato* db_buscarCandidatoPorNumero(const char* numero);

// --- Funções de Adição ---
bool db_adicionarEleitor(Eleitor novoEleitor);
bool db_adicionarCandidato(Candidato novoCandidato);

#endif // DATABASE_H

