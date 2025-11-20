# nome do executavel final
TARGET = urna_eletronica

# compilador c
CC = gcc

# flags do compilador
CFLAGS = -Wall -Wextra -g -std=c11

# lista de todos os arquivos fonte (.c)
# ATUALIZADO: adicionamos os dois novos modulos
SOURCES = \
    main.c \
    menu.c \
    utils.c \
    database.c \
    validacoes.c \
    eleitor.c \
    candidato.c \
    votacao.c \
    apuracao.c

# gera automaticamente a lista de arquivos objeto (.o)
OBJECTS = $(SOURCES:.c=.o)

# regras do make

# regra principal: compila tudo
all: $(TARGET)

# regra para linkar: junta todos os .o para criar o executavel
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# regra generica para compilar: transforma um .c em um .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# regra para limpar os arquivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)

# declara que 'all' e 'clean' nao sao nomes de arquivos
.PHONY: all clean