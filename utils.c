#include "utils.h"
#include "config.h" // Para printf, getchar, EOF, etc.

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        // Remove a nova linha (newline) do final, se existir
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

