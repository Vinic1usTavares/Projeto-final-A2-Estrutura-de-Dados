# Projeto Final — Entrega 1: Árvore Binária de Busca (BST)

Esta entrega contempla a implementação funcional da Árvore Binária de Busca (BST), a leitura de dados textuais para indexação e uma interface de linha de comando (CLI) para busca de palavras indexadas.

## Estrutura Entregue

- Implementação da estrutura BST com suporte à inserção e busca.
- Funções de leitura de documentos e processamento de palavras.
- CLI para execução de comandos de busca e estatísticas.
- Testes unitários para validação da funcionalidade da BST e do módulo de dados.

---

## Compilação

### Usando `make` (recomendado):

Para compilar o projeto completo (exceto o `test_data`):

```bash
make
```

Para compilar apenas a BST:

```bash
make bst
```

Para compilar apenas os testes do módulo `data`:

```bash
make test_data
```

---

### Manualmente via terminal (sem `make`):

Certifique-se de que os diretórios `bin/` e `obj/` existem. Caso não existam, crie-os com:

```bash
mkdir -p bin obj
```

#### Compilar a BST manualmente:

```bash
g++ -Wall -std=c++17 -Isrc -c src/main_bst.cpp -o obj/main_bst.o
g++ -Wall -std=c++17 -Isrc -c src/test_bst.cpp -o obj/test_bst.o
g++ -Wall -std=c++17 -Isrc -c src/bst.cpp -o obj/bst.o
g++ -Wall -std=c++17 -Isrc -c src/tree_utils.cpp -o obj/tree_utils.o
g++ -Wall -std=c++17 -Isrc -c src/data.cpp -o obj/data.o
g++ obj/main_bst.o obj/test_bst.o obj/bst.o obj/tree_utils.o obj/data.o -o bin/bst
```

#### Compilar os testes do módulo `data` manualmente:

```bash
g++ -Wall -std=c++17 -Isrc -c src/main_data.cpp -o obj/main_data.o
g++ -Wall -std=c++17 -Isrc -c src/test_data.cpp -o obj/test_data.o
g++ -Wall -std=c++17 -Isrc -c src/bst.cpp -o obj/bst.o
g++ -Wall -std=c++17 -Isrc -c src/tree_utils.cpp -o obj/tree_utils.o
g++ -Wall -std=c++17 -Isrc -c src/data.cpp -o obj/data.o
g++ obj/main_data.o obj/test_data.o obj/bst.o obj/tree_utils.o obj/data.o -o bin/test_data
```

---

## Uso

### Executar a BST:

```bash
./bin/bst <search> <número de documentos> <diretório de dados>
```

**Exemplo de busca:**

```bash
./bin/bst search 10 ./data
```

**Executar testes da BST:**

```bash
./bin/bst tests
```

### Executar os testes do módulo `data`:

```bash
./bin/test_data
```

Este programa executa testes de:

- Processamento de palavras (`process_words`)
- Indexação de documentos na estrutura BST (`index_documents` + `insert`)

---

## Requisitos

- Compilador `g++` com suporte a C++17
- `make` (opcional, mas recomendado)
- Ambiente Linux, macOS ou Windows com MSYS2/MinGW

---

## Diretórios

- `src/` — Código-fonte (estruturas, funções auxiliares, testes)
- `bin/` — Executáveis gerados
- `obj/` — Objetos compilados
- `data/` — Arquivos de entrada para testes de indexação
- `Makefile` — Automação da compilação e testes
