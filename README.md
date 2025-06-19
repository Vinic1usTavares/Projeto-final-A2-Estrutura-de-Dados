# # Projeto Final — Estruturas de Dados: Árvores Binárias (BST, AVL, RBT)

Este projeto contempla a implementação de estruturas de dados baseadas em árvores (BST, AVL e RBT), leitura de dados textuais, indexação, testes e interface de linha de comando (CLI) para busca e um relatório com estatísticas gerais das estruturas.

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
## Entrega 3 (final): Projeto completo + relatório + scripts e instruções

Esta entrega finaliza o projeto com a implementação da **árvore RBT**, com foco em um balanceamento menos rígido (em comparação com a **AVL**) e suporte completo a comandos da CLI, além do relatório projeto com a análise comparativa das estruturas.

### Estrutura Entregue

- Implementação da estrutura **RBT**, com balanceamento automático através de rotações simples e duplas.
- Suporte completo à **inserção balanceada** e **busca logarítmica**.
- CLI integrada com as seguintes funcionalidades:
  - Comando `search` — Busca por palavras indexadas.
  - Comando `stats` — Exibe estatísticas da árvore RBT (número de nós, altura da árvore, profundidade média etc.).
- Testes unitários específicos para a estrutura RBT, cobrindo casos de inserção e validação da árvore balanceada.

---

## Compilação com Make

Para compilar o projeto completo:

```bash
make
```

Ou, para compilar alvos específicos:

```bash
make bst        # Compila o programa com BST
make avl        # Compila o programa com AVL
make rbt        # Compila o programa com RBT
make test_data  # Compila os testes do módulo de dados
```

Para limpar os arquivos de build (executáveis e objetos):

```bash
make clean    # Deleta as pastas bin e obj
```

## Compilação Manual (sem Make)

Certifique-se de estar na raiz do projeto e que os diretórios `src/` e `bin/` existam. Use `g++` com suporte a C++17:

### Compilar a main_bst.cpp:

```bash
g++ -std=c++17 -Wall -Isrc src/main_bst.cpp src/bst.cpp src/test_bst.cpp src/data.cpp src/tree_utils.cpp -o bin/bst
```

### Compilar a main_avl.cpp:

```bash
g++ -std=c++17 -Wall -Isrc src/main_avl.cpp src/avl.cpp src/test_avl.cpp src/tree_utils.cpp src/data.cpp -o bin/avl
```

### Compilar a main_rbt.cpp:

```bash
g++ -std=c++17 -Wall -Isrc src/main_rbt.cpp src/rbt.cpp src/test_rbt.cpp src/tree_utils.cpp src/data.cpp -o bin/rbt
```

### Compilar os testes do módulo de dados:

```bash
g++ -std=c++17 -Wall -Isrc src/main_data.cpp src/test_data.cpp src/bst.cpp src/tree_utils.cpp src/data.cpp -o bin/test_data
```

---

## Uso

### Formato geral:

```bash
./bin/<estrutura> <comando> <n_docs> <diretório> 
```

Onde `<estrutura>` pode ser `bst`, `avl` ou `rbt`, e `<comando>` pode ser `search`, `stats` ou `tests`.

### Exemplos
#### BST:

```bash
./bin/bst search 10 data
./bin/bst stats 10 data
./bin/bst tests
```

#### AVL:

```bash
./bin/avl search 10 data
./bin/avl stats 10 data
./bin/av tests
```
#### RBT:

```bash
./bin/rbt search 10 data
./bin/rbt stats 10 data
./bin/rbt tests
```

### Execução dos testes do módulo `data`:

```bash
./bin/test_data
```

Esse programa executa testes de:

- Processamento de palavras (`process_words`)
    
- Indexação de documentos na estrutura BST (`index_documents` + `insert`)


---
## Geração de gráficos comparativos

Para comparar o desempenho e a estrutura das árvores (BST, AVL, RBT), foram desenvolvidos:

- Programas C++ para **gerar os dados estatísticos** em formato `.csv`
    
- Scripts Python para **gerar os gráficos** a partir desses dados
### Compilação dos geradores de dados

Primeiro crie as pastas ``bin`` e ``obj``.

```bash
# comparação do tempo de indexação/inserção
g++ -std=c++17 -Wall -Isrc docs/benchmark.cpp src/bst.cpp src/avl.cpp src/rbt.cpp src/data.cpp src/tree_utils.cpp -o bin/benchmark

# comparação do total de rotações acumuladas
g++ -std=c++17 -Wall -Isrc docs/benchmark.cpp src/bst.cpp src/avl.cpp src/rbt.cpp src/data.cpp src/tree_utils.cpp -o bin/benchmark

# comparação estrutural (altura, menor, caminho, total de comparações)
g++ -std=c++17 -Wall -Isrc docs/comparativo_estrutural.cpp src/bst.cpp src/avl.cpp src/rbt.cpp src/data.cpp src/tree_utils.cpp -o bin/comparativo_estrutural
```

### Execução para gerar os arquivos `.csv`

Execute os programas ``benchmark``, ``comparativo_estrutural`` e ``benchmark_rotations``  para gerar os dados nas pastas de saída:

### Uso

```bash
./bin/benchmark <diretorio_docs> <saida_csv>
./bin/benchmark <diretorio_docs> <saida_csv>
./bin/comparativo_estrutural <diretorio_docs> <saida_csv>
```

### Exemplo
```bash
./bin/benchmark data docs/tempo_indexacao.csv # Plot: comparação do tempo de indexação/inserção
./bin/comparativo_estrutural data docs/estrutura.csv # Plot:comparação estrutural (altura, menor, caminho, total de comparações)
```

## Geração de gráficos com Python

Execute:
```bash
python3 docs/plot.py
python3 docs/plot_estrutura_incremental.py
python3 docs/plot_rotations.py
python3 docs/analyze_results.py
```

### Saída:
O programa salva automaticamente os gráficos em ``docs/graficos``


---

## Requisitos
### C++:
- Compilador `g++` com suporte a C++17
    
- `make` (opcional, apenas para automação)
    
- Ambiente Linux, macOS ou Windows com MSYS2/MinGW
### Python:
- Python 3 instalado
    
- Bibliotecas:
    - `matplotlib`
        
    - `pandas`
            
    - `numpy`


---

## Diretórios

- `src/` — Código-fonte (estruturas, funções auxiliares, testes)
	
- ``docs/`` — Documentos referentes à análise comparativas das estruturas
		
	- ``graficos`` — gráficos das comparações
    
- `bin/` — Executáveis gerados
    
- `data/` — Arquivos de entrada para testes de indexação
    
- `Makefile` — Automação da compilação e testes  
