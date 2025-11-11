#ifndef UTILS_H
#define UTILS_H

// Limpa o buffer de entrada (essencial após usar scanf)
void limparBufferEntrada();

// Uma função segura para ler strings
void lerString(char *destino, int tamanho);

// Limpa a tela (multi-plataforma)
void limparTela();

#endif // UTILS_H

