# Detecta sistema operacional
OS := $(shell uname -s 2>/dev/null || echo Unknown)

# Diretórios
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

# Compilador e flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I$(SRC_DIR)

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(1)" mkdir "$(1)"
    LDFLAGS := -mconsole
    RMDIR = rmdir /S /Q
    RM = del /Q
else
    MKDIR = mkdir -p $(1)
    LDFLAGS :=
    RMDIR = rm -rf
    RM = rm -f
endif

# Fontes principais
BST_MAIN := $(SRC_DIR)/main_bst.cpp
DATA_MAIN := $(SRC_DIR)/main_data.cpp
AVL_MAIN := $(SRC_DIR)/main_avl.cpp

# Fontes comuns
COMMON_SRCS := $(SRC_DIR)/tree_utils.cpp $(SRC_DIR)/data.cpp

# Fontes de cada estrutura
BST_SRCS := $(SRC_DIR)/bst.cpp $(SRC_DIR)/test_bst.cpp
AVL_SRCS := $(SRC_DIR)/avl.cpp $(SRC_DIR)/test_avl.cpp
DATA_SRCS := $(SRC_DIR)/test_data.cpp $(SRC_DIR)/bst.cpp

# Fonte para testes avl
AVL_TEST := $(SRC_DIR)/test_avl.cpp

# Objetos comuns
COMMON_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(COMMON_SRCS))
BST_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(BST_SRCS)) $(COMMON_OBJS)
AVL_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(AVL_SRCS)) $(COMMON_OBJS)
DATA_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(DATA_SRCS)) $(COMMON_OBJS)

# Alvo principal
all: prepare bst test_data main_avl test_avl

# Criar diretórios
prepare:
	@$(call MKDIR,$(OBJ_DIR))
	@$(call MKDIR,$(BIN_DIR))

# Alvos
bst: prepare $(BST_OBJS) $(OBJ_DIR)/main_bst.o
	$(CXX) $(OBJ_DIR)/main_bst.o $(BST_OBJS) -o $(BIN_DIR)/bst $(LDFLAGS)

test_data: prepare $(DATA_OBJS) $(OBJ_DIR)/main_data.o
	$(CXX) $(OBJ_DIR)/main_data.o $(DATA_OBJS) -o $(BIN_DIR)/test_data $(LDFLAGS)

main_avl: prepare $(AVL_OBJS) $(OBJ_DIR)/main_avl.o
	$(CXX) $(OBJ_DIR)/main_avl.o $(AVL_OBJS) -o $(BIN_DIR)/main_avl $(LDFLAGS)

test_avl: prepare $(AVL_OBJS) $(OBJ_DIR)/test_avl.o
	$(CXX) $(OBJ_DIR)/test_avl.o $(AVL_OBJS) -o $(BIN_DIR)/test_avl $(LDFLAGS)

# Regras para compilar os arquivos .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# Limpeza
clean:
	-@$(RMDIR) $(OBJ_DIR)
	-@$(RMDIR) $(BIN_DIR)

.PHONY: all bst test_data main_avl test_avl clean prepare