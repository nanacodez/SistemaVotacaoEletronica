#include "menu.h"

int main() {
    int escolha = -1;

    do {
        // chama a funcao que esta em menu.c
        escolha = exibirMenuPrincipal();
        
        // chama a funcao que esta em menu.c
        processarEscolha(escolha);
        
    } while (escolha != 0);

    return 0;
}
