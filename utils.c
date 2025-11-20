// implementacao de funcoes utilitarias

#include "utils.h"
#include "config.h"

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) == NULL) {
        // lidar com erro de leitura, se necessario
        destino[0] = '\0';
        return;
    }

    // remove a nova linha (newline) do final se existir
    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') {
        destino[len - 1] = '\0';
    } else {
        // CORRECAO
        // se a nova linha NAO foi lida, o buffer esta sujo.
        // isso acontece se o usuario digitou mais que 'tamanho' caracteres
        // ou se era um buffer sujo de um scanf anterior, precisamos limpar o buffer.

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