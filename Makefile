# Diretórios
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

# Compilador e flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I$(SRC_DIR)

# Fontes principais
BST_MAIN := $(SRC_DIR)/main_bst.cpp
AVL_MAIN := $(SRC_DIR)/main_avl.cpp
DATA_MAIN := $(SRC_DIR)/main_data.cpp

# Fontes comuns
COMMON_SRCS := $(SRC_DIR)/tree_utils.cpp $(SRC_DIR)/data.cpp
COMMON_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(COMMON_SRCS))

# Fontes específicas
BST_SRCS := $(SRC_DIR)/bst.cpp $(SRC_DIR)/test_bst.cpp
AVL_SRCS := $(SRC_DIR)/avl.cpp $(SRC_DIR)/test_avl.cpp
DATA_SRCS := $(SRC_DIR)/test_data.cpp $(SRC_DIR)/bst.cpp

# Objetos
BST_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(BST_SRCS)) $(COMMON_OBJS)
AVL_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(AVL_SRCS)) $(COMMON_OBJS)
DATA_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(DATA_SRCS)) $(COMMON_OBJS)

# Alvo principal
all: prepare bst avl test_data

# Criar diretórios
prepare:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Alvos
bst: $(BST_OBJS) $(OBJ_DIR)/main_bst.o
	$(CXX) $^ -o $(BIN_DIR)/bst

avl: $(AVL_OBJS) $(OBJ_DIR)/main_avl.o
	$(CXX) $^ -o $(BIN_DIR)/avl

test_data: $(DATA_OBJS) $(OBJ_DIR)/main_data.o
	$(CXX) $^ -o $(BIN_DIR)/test_data

# Regra geral de compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all bst avl test_data clean prepare
