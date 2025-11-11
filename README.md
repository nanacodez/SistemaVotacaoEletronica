# 🗳️ Urna Eletrônica (Sistema de Votação)

Um sistema de votação eletrônica completo, com cadastro, votação e apuração, implementado em duas versões: C modular e Aplicação Web (HTML/CSS/JS).

Este projeto simula o ciclo de vida completo de uma eleição, desde o cadastro de eleitores e candidatos até a apuração e auditoria dos votos.

---

## 📜 Sumário

* [Sobre o Projeto](#sobre-o-projeto)
* [Funcionalidades](#-funcionalidades)
* [Tecnologias Utilizadas](#-tecnologias-utilizadas)
* [Como Executar](#-como-executar)
    * [Versão C (Console)](#1-versão-c-console)
    * [Versão Web (Navegador)](#2-versão-web-navegador)
* [Estrutura do Projeto C](#-estrutura-do-projeto-c)
* [Licença](#-licença)

---

## 🚀 Sobre o Projeto

Este projeto foi desenvolvido como um sistema robusto para simular uma urna eletrônica. Ele é dividido em duas implementações distintas com o mesmo conjunto de regras de negócio:

1.  **Versão C:** Uma aplicação de console focada em **engenharia de software**, **modularidade** e **gerenciamento de memória**. O código é dividido em módulos lógicos (ex: `database`, `votacao`, `apuracao`), demonstrando os princípios de encapsulamento e separação de responsabilidades.
2.  **Versão Web:** Uma aplicação *front-end* (cliente-side) que recria toda a lógica do programa C em **JavaScript**. Ela oferece uma interface gráfica de usuário (GUI) amigável, rodando inteiramente no navegador, com o estado da aplicação (banco de dados) sendo mantido em memória.

Ambas as versões garantem a integridade dos dados, como o controle de duplicidade de eleitores/candidatos e a verificação de voto único.

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

| Versão | Tecnologia | Descrição |
| :--- | :--- | :--- |
| **C (Console)** | `C (GCC/C11)` | Linguagem principal para a lógica do sistema. |
| | `Makefile` | Gerenciador de compilação para o projeto C modular. |
| **Web (Front-End)** | `HTML5` | Estrutura e semântica da aplicação web. |
| | `CSS3` | Estilização da interface de usuário. |
| | `JavaScript (ES6+)` | Reimplementação de toda a lógica C para interatividade no navegador. |

---

## 🏃 Como Executar

Você pode executar qualquer uma das duas versões do projeto.

### 1. Versão C (Console)

Esta versão requer um compilador C (como `gcc`) e a ferramenta `make` instalados em seu sistema.

```bash
# 1. Navegue até o diretório do projeto C
cd /caminho/para/o/projeto_c

# 2. Limpe compilações anteriores (opcional, mas recomendado)
make clean

# 3. Compile o projeto
# O Makefile irá gerenciar todos os arquivos .c e .h
make

# 4. Execute o programa
./urna_eletronica