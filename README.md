# 🗳️ Urna Eletrônica (Sistema de Votação em C)

Este projeto é uma simulação de sistema de votação eletrônica completo, desenvolvido em linguagem C com foco em modularidade, engenharia de software e gerenciamento de memória.

Ele simula o ciclo de vida completo de uma eleição, desde o cadastro de eleitores e candidatos até a apuração e auditoria dos votos.

---

## 📜 Sumário

* [Sobre o Projeto](#sobre-o-projeto)
* [Funcionalidades](#-funcionalidades)
* [Tecnologias Utilizadas](#-tecnologias-utilizadas)
* [Como Compilar e Executar](#-como-compilar-e-executar)
* [Estrutura do Projeto](#-estrutura-do-projeto)
* [Licença](#-licença)

---

## 🚀 Sobre o Projeto

Este projeto foi desenvolvido como uma aplicação de console robusta para simular uma urna eletrônica. O código é dividido em módulos lógicos (ex: `database`, `votacao`, `apuracao`), demonstrando os princípios de encapsulamento e separação de responsabilidades.

O sistema garante a integridade dos dados, como o controle de duplicidade de eleitores/candidatos e a verificação de voto único.

---

## ✨ Funcionalidades

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

## 💻 Tecnologias Utilizadas

| Tecnologia | Descrição |
| :--- | :--- |
| **C (GCC/C11)** | Linguagem principal para a lógica do sistema. |
| **Makefile** | Gerenciador de compilação para o projeto C modular. |

---

## 🏃 Como Compilar e Executar

Este projeto requer um compilador C (como `gcc`) e a ferramenta `make` instalados em seu sistema.

```bash
# 1. Navegue até o diretório do projeto C
cd /caminho/para/o/projeto

# 2. Limpe compilações anteriores (opcional, mas recomendado)
make clean

# 3. Compile o projeto
# O Makefile irá gerenciar todos os arquivos .c e .h
make

# 4. Execute o programa
./urna_eletronica
````

-----

## 🏗️ Estrutura do Projeto

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
      * Define constantes globais (ex: `MAX_ELETORES`).

-----

## ⚖️ Licença

Distribuído sob a licença MIT. Veja `LICENSE` para mais informações.

````

---

### 2. Guia: Instalando e Usando o `make` no VS Code

O VS Code é apenas um editor de texto; ele não vem com um compilador C. Precisamos instalar o **"C Toolchain"** (o kit de ferramentas C), que inclui o compilador **`gcc`** e o utilitário **`make`**.

O processo varia dependendo do seu sistema operacional.

#### Passo A: Instalando os Programas Necessários

Escolha o seu sistema operacional:

---
##### 🐧 Para Linux (Baseado em Ubuntu/Debian)
Este é o ambiente mais fácil, pois as ferramentas são padrão.

1.  Abra o seu terminal (pode ser fora do VS Code por enquanto).
2.  Execute o comando para instalar o pacote `build-essential`. Ele inclui tudo ( `gcc`, `g++`, `make`, etc.):
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```
3.  Para verificar, digite `gcc --version` e `make --version`. Se eles mostrarem números de versão, você está pronto.

---
##### 🪟 Para Windows (O Mais Comum)
No Windows, precisamos instalar um ambiente que simula o Linux. A melhor opção é o **MSYS2**, que fornece o `MinGW-w64` (que inclui `gcc` e `make`).

1.  **Instale o MSYS2:**
    * Vá para [https://www.msys2.org/](https://www.msys2.org/) e baixe o instalador.
    * Siga as instruções de instalação (pode deixar no local padrão `C:\msys64`).
2.  **Abra o Terminal MSYS2:**
    * Após a instalação, procure por "MSYS2 MSYS" no menu Iniciar e abra-o.
3.  **Instale o Toolchain (gcc e make):**
    * Dentro desse terminal do MSYS2, digite o seguinte comando:
        ```bash
        pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
        ```
    * Pressione Enter para confirmar a seleção padrão (instalar tudo).
4.  **🛑 (O Passo Mais Importante) Adicione o Compilador ao PATH:**
    * O VS Code precisa *encontrar* o `gcc.exe` e `make.exe` que você acabou de instalar.
    * No Windows, pesquise por "Editar as variáveis de ambiente do sistema".
    * Clique em "Variáveis de Ambiente...".
    * Na seção "Variáveis do sistema", encontre a variável `Path` e clique em "Editar...".
    * Clique em "Novo" e adicione o caminho para a pasta `bin` do seu compilador. O caminho padrão é:
        `C:\msys64\ucrt64\bin`
    * Clique em "OK" em todas as janelas.
    * **Feche e reabra o VS Code** para que ele reconheça a mudança.

---
##### 🍎 Para macOS
O macOS já vem com ferramentas, mas você precisa ativá-las com o "Xcode Command Line Tools".

1.  Abra o Terminal.
2.  Digite o comando:
    ```bash
    xcode-select --install
    ```
3.  Uma janela pop-up aparecerá. Clique em "Instalar". Isso baixará `gcc` (na verdade, é o `clang`, um substituto compatível) e `make`.

#### Passo B: Usando o `make` no Terminal do VS Code

Agora que as ferramentas estão instaladas, o fluxo de trabalho é o mesmo para todos os sistemas:

1.  **Abra seu Projeto no VS Code:**
    * No VS Code, vá em `Arquivo` > `Abrir Pasta...` (ou `File` > `Open Folder...`).
    * Selecione a pasta principal do seu projeto (a que contém todos os `.c` e `.h`).
2.  **Abra o Terminal Integrado:**
    * No menu superior, vá em `Terminal` > `Novo Terminal` (ou `Terminal` > `New Terminal`).
    * Você também pode usar o atalho: **`Ctrl + `** (Control + Aspa simples/crase).
    * 
3.  **Verifique a Instalação:**
    * No terminal que acabou de abrir (dentro do VS Code), digite `gcc --version` e `make --version`. Se eles funcionarem, o Passo A foi um sucesso. Se não (especialmente no Windows), seu `PATH` está errado.
4.  **Use os Comandos do `make`:**
    * Agora você pode usar o `make` exatamente como descrito no `README.md`.

    * **Para Compilar (Construir):**
        ```bash
        make
        ```
        * **O que ele faz?** O `make` lê o seu `Makefile`. Ele vê que você quer criar o alvo `urna_eletronica`. Ele então procura os arquivos "objeto" (`.o`). Ele vê que `main.o` depende de `main.c`. Ele compila `main.c` para criar `main.o`, e faz o mesmo para todos os outros `.c`. No final, ele "linka" (junta) todos os `.o` para criar o executável final `urna_eletronica`.

    * **Para Executar:**
        ```bash
        ./urna_eletronica
        ```
        * (No Windows (cmd ou PowerShell), você pode digitar apenas `urna_eletronica.exe`)

    * **Para Limpar:**
        ```bash
        make clean
        ```
        * **Por que usar?** Às vezes, você pode querer forçar uma recompilação total. O `make` é inteligente; ele só recompila os arquivos que *mudaram* desde a última vez. `make clean` apaga todos os `.o` e o executável, forçando o `make` a reconstruir tudo do zero na próxima vez.

#### Dica Bônus: A Extensão C/C++ da Microsoft

Para tornar sua vida no VS Code ainda melhor:

1.  Vá para a aba de **Extensões** (o ícone de blocos no lado esquerdo).
2.  Procure por **"C/C++"** da Microsoft e instale-a.
3.  Isso lhe dará "IntelliSense" (autocompletar código), realce de sintaxe e, o mais importante, a habilidade de usar o **depurador (debugger)** visual do VS Code, para que você possa executar seu código linha por linha e inspecionar variáveis.