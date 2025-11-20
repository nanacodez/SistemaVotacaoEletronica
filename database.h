#ifndef DATABASE_H
#define DATABASE_H

#include "modelos.h"

// getters de contagem 
int db_getTotalEleitores();
int db_getTotalCandidatos();

// getters de objetos 
Eleitor* db_getEleitorPorIndice(int indice);
Candidato* db_getCandidatoPorIndice(int indice);

// funcoes de busca (para validacao) 
Eleitor* db_buscarEleitorPorTitulo(const char* titulo);
Candidato* db_buscarCandidatoPorNumero(const char* numero);

// funcoes de adicao
bool db_adicionarEleitor(Eleitor novoEleitor);
bool db_adicionarCandidato(Candidato novoCandidato);

#endif // DATABASE_H

