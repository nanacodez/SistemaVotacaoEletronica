#include "menu.h"

/*
 * =========================================
 * 7. FUNÇÃO MAIN (MENU PRINCIPAL)
 * =========================================
 */

int main() {
    int escolha = -1;

    do {
        escolha = exibirMenuPrincipal();
        processarEscolha(escolha);
    } while (escolha != 0);

    return 0;
}