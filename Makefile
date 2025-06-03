# Diretórios
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

# Compilador e flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I$(SRC_DIR)
LDFLAGS := -mconsole  # 👈 FORÇA PROGRAMA DE TERMINAL NO WINDOWS

# Fontes principais
BST_MAIN := $(SRC_DIR)/main_bst.cpp
AVL_MAIN := $(SRC_DIR)/main_avl.cpp
RBT_MAIN := $(SRC_DIR)/main_rbt.cpp

# Fontes comuns
COMMON_SRCS := $(SRC_DIR)/tree_utils.cpp $(SRC_DIR)/data.cpp

# Fontes de cada estrutura
BST_SRCS := $(SRC_DIR)/bst.cpp
AVL_SRCS := $(SRC_DIR)/avl.cpp
RBT_SRCS := $(SRC_DIR)/rbt.cpp

# Objetos comuns
COMMON_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(COMMON_SRCS))
BST_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(BST_SRCS)) $(COMMON_OBJS)
AVL_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(AVL_SRCS)) $(COMMON_OBJS)
RBT_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(RBT_SRCS)) $(COMMON_OBJS)

# Alvo principal
all: prepare bst avl rbt

# Criar diretórios
prepare:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Alvos
bst: prepare $(BST_OBJS) $(OBJ_DIR)/main_bst.o
	$(CXX) $(OBJ_DIR)/main_bst.o $(BST_OBJS) -o $(BIN_DIR)/bst $(LDFLAGS)

avl: prepare $(AVL_OBJS) $(OBJ_DIR)/main_avl.o
	$(CXX) $(OBJ_DIR)/main_avl.o $(AVL_OBJS) -o $(BIN_DIR)/avl $(LDFLAGS)

rbt: prepare $(RBT_OBJS) $(OBJ_DIR)/main_rbt.o
	$(CXX) $(OBJ_DIR)/main_rbt.o $(RBT_OBJS) -o $(BIN_DIR)/rbt $(LDFLAGS)

# Regras para compilar os arquivos .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all bst avl rbt clean prepare
