# Projeto Final — Entregas: Árvores Binárias (BST e AVL)

Este projeto contempla a implementação de estruturas de dados baseadas em árvores (BST e AVL), leitura de dados textuais, indexação, testes e interface de linha de comando (CLI) para busca e estatísticas.

---

## Entrega 1: Árvore Binária de Busca (BST)

Esta entrega contempla a implementação funcional da Árvore Binária de Busca (BST), a leitura de dados textuais para indexação e uma interface de linha de comando (CLI) para busca de palavras indexadas.

### Estrutura Entregue

- Implementação da estrutura **BST** com suporte à **inserção** e **busca**.
- Funções de leitura de documentos e processamento de palavras.
- CLI para execução de comandos de **busca** e **estatísticas**.
- Testes unitários para validação da funcionalidade da BST e do módulo de dados.

---

## Entrega 2: AVL funcional + CLI (Estatísticas)

Esta entrega amplia o projeto com a implementação da **árvore AVL**, com foco em balanceamento automático das inserções e suporte completo a comandos da CLI.

### Estrutura Entregue

- Implementação da estrutura **AVL**, com balanceamento automático através de rotações simples e duplas.
- Suporte completo à **inserção balanceada** e **busca logarítmica**.
- CLI integrada com as seguintes funcionalidades:
  - Comando `search` — Busca por palavras indexadas.
  - Comando `stats` — Exibe estatísticas da árvore AVL (número de nós, altura da árvore, profundidade média etc.).
- Testes unitários específicos para a estrutura AVL, cobrindo casos de inserção e validação da árvore balanceada.

---

## Compilação com Make

Para compilar o projeto completo (fora `test_data`):

```bash
make
```

Ou, para compilar alvos específicos:

```bash
make bst        # Compila o programa com BST
make avl        # Compila o programa com AVL
make test_data  # Compila os testes do módulo de dados
```

## Compilação Manual (sem Make)

Certifique-se de estar na raiz do projeto e que os diretórios `src/` e `bin/` existam. Use `g++` com suporte a C++17:

### Compilar a main da BST:

```bash
g++ -std=c++17 -Wall -Isrc src/main_bst.cpp src/bst.cpp src/test_bst.cpp src/data.cpp src/tree_utils.cpp -o bin/bst
```

### Compilar a main da AVL:

```bash
g++ -std=c++17 -Wall -Isrc src/main_avl.cpp src/avl.cpp src/test_avl.cpp src/tree_utils.cpp src/data.cpp -o bin/avl
```

### Compilar os testes do módulo de dados:

```bash
g++ -std=c++17 -Wall -Isrc src/main_data.cpp src/test_data.cpp src/bst.cpp src/tree_utils.cpp src/data.cpp -o bin/test_data
```

---

## Uso

### Execução da BST:

```bash
 ./bin/bst <search> <número de documentos> <diretorio de dados>
```

**Exemplo de busca:**

```bash
./bin/bst search 10 data
```

**Execução dos testes da BST:**

```bash
./bin/bst tests
```

### Execução da AVL:
```bash
./bin/main_avl <search|stats> <número de documentos> <diretorio de dados>
```

**Exemplo de busca:**

```bash
./bin/main_avl search 10 data
```
**Exemplo de estatísticas:**

```bash
./bin/main_avl stats 10 data
```

**Execução dos testes da BST:**

```bash
./bin/bst tests
```


### Execução dos testes do módulo `data`:

```bash
./bin/test_data
```

Esse programa executa testes de:

- Processamento de palavras (`process_words`)
    
- Indexação de documentos na estrutura BST (`index_documents` + `insert`)
    

---

## Requisitos

- Compilador `g++` com suporte a C++17
    
- `make` (opcional, apenas para automação)
    
- Ambiente Linux, macOS ou Windows com MSYS2/MinGW
    

---

## Diretórios

- `src/` — Código-fonte (estruturas, funções auxiliares, testes)
    
- `bin/` — Executáveis gerados
    
- `data/` — Arquivos de entrada para testes de indexação
    
- `Makefile` — Automação da compilação e testes  