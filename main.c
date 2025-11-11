/*
 * ===================================================================
 * ARQUIVO: main.c
 * DESCRIÇÃO: Ponto de entrada (contém apenas o loop principal).
 * ===================================================================
 */

#include "menu.h"

int main() {
    int escolha = -1;

    do {
        // Chama a função que está em menu.c
        escolha = exibirMenuPrincipal();
        
        // Chama a função que está em menu.c
        processarEscolha(escolha);
        
    } while (escolha != 0);

    return 0;
}
