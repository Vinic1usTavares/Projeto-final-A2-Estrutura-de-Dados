/**
 * @file data.h
 * @brief Interface para processamento de dados e indexação em estruturas de árvore.
 * 
 * Este cabeçalho define funções para:
 * - Processamento de texto
 * - Carregamento de documentos
 * - Indexação em árvores binárias
 */

#ifndef DATA_H
#define DATA_H

#include <vector>
#include "tree_utils.h"
#include <string>
#include <functional>
#include <sstream>

/**
 * @brief Processa um texto extraindo palavras normalizadas.
 * @param text Texto de entrada a ser processado.
 * @return Vetor de strings contendo palavras processadas (minúsculas, sem caracteres especiais).
 * @note Remove pontuação e converte para minúsculas. Ex: "Hello, World!" → ["hello", "world"]
 */
std::vector<std::string> process_words(const std::string& text);

/**
 * @brief Carrega documentos de um diretório.
 * @param dir Caminho do diretório contendo os documentos.
 * @param n_docs Número de documentos a carregar (0.txt a (n_docs-1).txt).
 * @return Vetor de pares <conteúdo, ID> onde ID é o número do documento.
 * @warning Emite mensagens de erro se o diretório ou arquivos não forem encontrados.
 */
std::vector<std::pair<std::string, int>> load_documents(const std::string& dir, int n_docs);

/**
 * @brief Indexa palavras de documentos em uma árvore binária.
 * @param tree Ponteiro para a árvore de indexação.
 * @param docs Vetor de documentos retornado por load_documents().
 * @param insert_function Função de inserção específica (ex: AVL::insert).
 * @return Vetor de resultados de inserção para rastreamento.
 * @see BinaryTree, InsertResult
 */
std::vector<InsertResult> index_documents(
    BinaryTree* tree,
    const std::vector<std::pair<std::string, int>>& docs,
    std::function<InsertResult(BinaryTree*, const std::string&, int)> insert_function
);

/**
 * @brief Função utilitária para conversão case-insensitive.
 * @param c Caractere a ser convertido.
 * @return Versão minúscula do caractere se for A-Z, caso contrário retorna o próprio caractere.
 */
char to_lower(char c);

#endif // DATA_H