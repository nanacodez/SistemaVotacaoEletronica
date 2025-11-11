# Nome do executável final
TARGET = urna_eletronica

# Compilador C
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -g -std=c11

# Lista de todos os arquivos fonte (.c)
# ATUALIZADO: Adicionamos os dois novos módulos
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

# Gera automaticamente a lista de arquivos objeto (.o)
OBJECTS = $(SOURCES:.c=.o)

# --- Regras do Make ---

# Regra principal: compila tudo
all: $(TARGET)

# Regra para linkar: junta todos os .o para criar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra genérica para compilar: transforma um .c em um .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Declara que 'all' e 'clean' não são nomes de arquivos
.PHONY: all clean