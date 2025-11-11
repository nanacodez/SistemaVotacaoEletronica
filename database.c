#include "database.h"

/*
 * =========================================
 * 3. BANCO DE DADOS (SIMULADO)
 * =========================================
 * Estes arrays e contadores são 'static'.
 * Isso significa que eles SÓ podem ser vistos
 * dentro deste arquivo (database.c).
 * Isso é encapsulamento!
 */

static Eleitor db_eleitores[MAX_ELEITORES];
static Candidato db_candidatos[MAX_CANDIDATOS];

static int totalEleitores = 0;
static int totalCandidatos = 0;

// --- Implementação das Funções ---

int db_getTotalEleitores() {
    return totalEleitores;
}

int db_getTotalCandidatos() {
    return totalCandidatos;
}

Eleitor* db_getEleitorPorIndice(int indice) {
    if (indice < 0 || indice >= totalEleitores) {
        return NULL; // Índice inválido
    }
    return &db_eleitores[indice];
}

Candidato* db_getCandidatoPorIndice(int indice) {
    if (indice < 0 || indice >= totalCandidatos) {
        return NULL; // Índice inválido
    }
    return &db_candidatos[indice];
}

Eleitor* db_buscarEleitorPorTitulo(const char* titulo) {
    for (int i = 0; i < totalEleitores; i++) {
        if (strcmp(db_eleitores[i].tituloEleitor, titulo) == 0) {
            return &db_eleitores[i];
        }
    }
    return NULL; // Não encontrado
}

Candidato* db_buscarCandidatoPorNumero(const char* numero) {
    for (int i = 0; i < totalCandidatos; i++) {
        if (strcmp(db_candidatos[i].numero, numero) == 0) {
            return &db_candidatos[i];
        }
    }
    return NULL; // Não encontrado
}

bool db_adicionarEleitor(Eleitor novoEleitor) {
    if (totalEleitores >= MAX_ELEITORES) {
        return false; // Banco cheio
    }
    db_eleitores[totalEleitores] = novoEleitor;
    totalEleitores++;
    return true;
}

bool db_adicionarCandidato(Candidato novoCandidato) {
    if (totalCandidatos >= MAX_CANDIDATOS) {
        return false; // Banco cheio
    }
    db_candidatos[totalCandidatos] = novoCandidato;
    totalCandidatos++;
    return true;
}