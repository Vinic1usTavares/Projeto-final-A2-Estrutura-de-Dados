# Configurações do compilador
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
LDFLAGS := 

# Lista de executáveis
TARGETS := bst avl rbt

# Arquivos fonte principais
BST_MAIN := main_bst.cpp
AVL_MAIN := main_avl.cpp
RBT_MAIN := main_rbt.cpp

# Arquivos fonte comuns
COMMON_SRCS := tree_utils.cpp data.cpp
BST_SRCS := bst.cpp
AVL_SRCS := avl.cpp
RBT_SRCS := rbt.cpp

# Geração automática de objetos
COMMON_OBJS := $(COMMON_SRCS:.cpp=.o)
BST_OBJS := $(BST_SRCS:.cpp=.o) $(COMMON_OBJS)
AVL_OBJS := $(AVL_SRCS:.cpp=.o) $(COMMON_OBJS)
RBT_OBJS := $(RBT_SRCS:.cpp=.o) $(COMMON_OBJS)

# Alvo principal
all: $(TARGETS)

# Regras para os executáveis
bst: $(BST_MAIN:.cpp=.o) $(BST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

avl: $(AVL_MAIN:.cpp=.o) $(AVL_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

rbt: $(RBT_MAIN:.cpp=.o) $(RBT_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regra genérica para compilar .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean