#ifndef UTILS_H
#define UTILS_H

// limpa o buffer de entrada (essencial após usar scanf)
void limparBufferEntrada();

// uma funcao segura para ler strings
void lerString(char *destino, int tamanho);

// limpa a tela (multi-plataforma)
void limparTela();

#endif // UTILS_H

