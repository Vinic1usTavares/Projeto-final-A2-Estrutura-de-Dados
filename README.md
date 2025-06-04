# Projeto Final — Entrega 1: Árvore Binária de Busca (BST)

Esta entrega contempla a implementação funcional da Árvore Binária de Busca (BST), a leitura de dados textuais para indexação e uma interface de linha de comando (CLI) para busca de palavras indexadas.

## Estrutura Entregue

- Implementação da estrutura BST com suporte à inserção e busca.
- Funções de leitura de documentos e processamento de palavras.
- CLI para execução de comandos de busca e estatísticas.
- Testes unitários para validação da funcionalidade da BST e do módulo de dados.

## Compilação

Para compilar o projeto completo (fora test_data):

```bash
make
```

Ou, para compilar apenas a BST:

```bash
make bst
```

Para compilar os testes do módulo de dados:

```bash
make test_data
```

## Uso

### Execução da BST:

```bash
./bin/bst <search> <número de documentos> <diretorio de dados>
```

**Exemplo de busca:**
```bash
./bin/bst search 10 ./data
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

## Requisitos

- Compilador `g++` com suporte a C++17
- `make`
- Ambiente Linux, macOS ou Windows com MSYS2/MinGW

## Diretórios

- `src/` — Código-fonte (estruturas, funções auxiliares, testes)
- `bin/` — Executáveis gerados
- `data/` — Arquivos de entrada para testes de indexação
- `Makefile` — Automação da compilação e testes
