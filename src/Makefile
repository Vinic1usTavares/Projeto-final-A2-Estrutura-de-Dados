# Compilador e flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -O2

# Lista de executáveis principais
MAIN_TARGETS := main_avl main_bst main_data main_tbt

# Lista de executáveis de teste
TEST_TARGETS := test_bst test_data test

# Todos os alvos
TARGETS := $(MAIN_TARGETS) $(TEST_TARGETS)

# Objetos compartilhados
SHARED_OBJS := avl.o bst.o rbt.o data.o tree_utils.o

# Regra principal
all: $(TARGETS)

# Regras para executáveis principais
main_avl: main_avl.o $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

main_bst: main_bst.o $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

main_data: main_data.o data.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main_tbt: main_tbt.o rbt.o data.o tree_utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regras para executáveis de teste
test_bst: test_bst.o bst.o tree_utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test_data: test_data.o data.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test: test.o $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regra genérica para objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean