/*
 * ===================================================================
 * ARQUIVO: utils.c
 * DESCRIÇÃO: Implementação de funções utilitárias.
 * ===================================================================
 */

#include "utils.h"
#include "config.h" // Para printf, getchar, EOF, etc.

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//
// ===== FUNÇÃO ATUALIZADA =====
//
void lerString(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) == NULL) {
        // Lidar com erro de leitura, se necessário
        destino[0] = '\0';
        return;
    }

    // Remove a nova linha (newline) do final, se existir
    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') {
        destino[len - 1] = '\0';
    } else {
        //
        // --- A CORREÇÃO ESTÁ AQUI ---
        // Se a nova linha NÃO foi lida, o buffer está sujo.
        // Isso acontece se o usuário digitou mais que 'tamanho' caracteres
        // ou se era um buffer sujo de um scanf anterior.
        // Precisamos limpar o buffer.
        //
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}


void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}