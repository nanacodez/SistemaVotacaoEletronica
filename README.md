#  Urna Eletrônica (Sistema de Votação em C)

Este projeto é uma simulação de sistema de votação eletrônica completo, desenvolvido em linguagem C com foco em modularidade, engenharia de software e gerenciamento de memória.

Ele simula o ciclo de vida completo de uma eleição, desde o cadastro de eleitores e candidatos até a apuração e auditoria dos votos.

---

##  Sumário

* [Sobre o Projeto](#sobre-o-projeto)
* [Funcionalidades](#-funcionalidades)
* [Tecnologias Utilizadas](#-tecnologias-utilizadas)
* [Como Compilar e Executar (Guia VS Code)](#-como-compilar-e-executar-guia-vs-code)
* [Estrutura do Projeto](#-estrutura-do-projeto)
* [Licença](#-licença)

---

##  Sobre o Projeto

Este projeto foi desenvolvido como uma aplicação de console robusta para simular uma urna eletrônica. O código é dividido em módulos lógicos (ex: `database`, `votacao`, `apuracao`), demonstrando os princípios de encapsulamento e separação de responsabilidades.

O sistema garante a integridade dos dados, como o controle de duplicidade de eleitores/candidatos e a verificação de voto único.

---

##  Funcionalidades

O sistema permite um fluxo completo de eleição em três fases:

* **Fase 1: Cadastro**
    * [x] Cadastrar Eleitores (com validação de idade e título único).
    * [x] Cadastrar Candidatos (com validação de número único).
    * [x] Listar eleitores e candidatos cadastrados.

* **Fase 2: Votação**
    * [x] Autenticação do eleitor pelo Título.
    * [x] Controle de voto único (impede que um eleitor vote duas vezes).
    * [x] Lógica de voto para **candidato válido**, **voto nulo** e **voto em branco**.

* **Fase 3: Apuração**
    * [x] Contagem e totalização dos votos (nominais, nulos, brancos).
    * [x] Ordenação dos candidatos por número de votos.
    * [x] **Auditoria de Integridade**: Verifica se o número total de votos na urna é igual ao número de eleitores que votaram.

---

##  Tecnologias Utilizadas

| Tecnologia | Descrição |
| :--- | :--- |
| **C (GCC/C11)** | Linguagem principal para a lógica do sistema. |
| **Makefile** | Gerenciador de compilação para o projeto C modular. |

---

##  Como Compilar e Executar (Guia VS Code)

Para compilar e rodar este projeto no terminal do VS Code, você primeiro precisa das ferramentas corretas (`gcc` e `make`) e depois seguir o fluxo de compilação.

### 1. Instalação das Ferramentas (Compilador)

O VS Code é um editor de texto; o compilador C é instalado separadamente.

* **No Windows (Usando MSYS2/MinGW):**
    * **Passo 1:** Baixe e instale o **MSYS2** (do site [msys2.org](https://www.msys2.org/)).
    * **Passo 2:** No terminal "MSYS2 MSYS" (que você acabou de instalar), execute:
        `pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain`
    * **Passo 3 (Obrigatório):** Adicione o compilador ao `PATH` do Windows.
        1.  Procure por "Editar as variáveis de ambiente do sistema".
        2.  Clique em "Variáveis de Ambiente...".
        3.  Na seção "Variáveis do sistema", selecione `Path` e clique em "Editar".
        4.  Clique em "Novo" e adicione o caminho: `C:\msys64\ucrt64\bin`
        5.  Clique "OK" em tudo e **reinicie o VS Code**.

* **No Linux (Ubuntu/Debian):**
    * **Passo 1:** No seu terminal, execute o comando:
        `sudo apt update && sudo apt install build-essential`
    * (Isso instala `gcc`, `g++`, `make` e outras ferramentas essenciais).

* **No macOS:**
    * **Passo 1:** No seu terminal, execute o comando:
        `xcode-select --install`
    * (Isso instala as Ferramentas de Linha de Comando do Xcode, que incluem `clang` (compilador) e `make`).

### 2. Fluxo de Trabalho no VS Code

* **Abrir o Projeto:**
    * No VS Code, vá em `Arquivo` > `Abrir Pasta...` e selecione o diretório do seu projeto (onde está o `Makefile`).


* **Abrir o Terminal Integrado:**
    * Use o atalho `Ctrl + '` (Control + Aspa simples/crase) para abrir o terminal.

* **Extensão C/C++ (Recomendado):**
    * Na aba de Extensões (ícone de blocos), procure e instale a extensão **"C/C++"** da Microsoft. Isso ativa o autocompletar e a depuração.

* **Comando `make` (Compilar):**
    * No terminal do VS Code, digite `make`.
    * **O que faz:** Ele lê o `Makefile`, compila todos os arquivos `.c` necessários em arquivos `.o` (objetos) e os "linka" (junta) para criar o executável final: `urna_eletronica`.

* **Comando `./urna_eletronica` (Executar):**
    * No mesmo terminal, digite `./urna_eletronica` para rodar o programa.
    * **Nota Windows:** Se estiver no PowerShell, o comando é `.\urna_eletronica.exe`. Se estiver no CMD, é só `urna_eletronica.exe`.

* **Comando `make clean` (Limpar):**
    * No terminal, digite `make clean`.
    * **O que faz:** Apaga todos os arquivos gerados pela compilação (`.o` e o executável). É útil quando você quer forçar uma recompilação total do zero.

---

##  Estrutura do Projeto

O projeto foi projetado com alta coesão e baixo acoplamento, separando responsabilidades em módulos distintos:

* **`main.c` / `menu.h` / `menu.c`**
    * Controla o fluxo principal e a interface do usuário (menu).
* **`modelos.h`**
    * Define as `structs` de dados (ex: `Eleitor`, `Candidato`).
* **`database.h` / `database.c`**
    * **Encapsula** os dados (arrays e contadores), permitindo o acesso apenas através de funções.
* **`eleitor.h` / `eleitor.c`**
    * Gerencia a lógica de negócio para Eleitores (cadastro, listagem).
* **`candidato.h` / `candidato.c`**
    * Gerencia a lógica de negócio para Candidatos.
* **`votacao.h` / `votacao.c`**
    * Gerencia a lógica do processo de votação.
* **`apuracao.h` / `apuracao.c`**
    * Gerencia a lógica de contagem, ordenação e auditoria dos votos.
* **`validacoes.h` / `validacoes.c`**
    * Funções puras para validar dados (ex: `validarTitulo`, `validarIdade`).
* **`utils.h` / `utils.c`**
    * Funções auxiliares genéricas (ex: `limparTela`, `lerString`).
* **`config.h`**
    * Define constantes globais (ex: `MAX_ELEITORES`).

---