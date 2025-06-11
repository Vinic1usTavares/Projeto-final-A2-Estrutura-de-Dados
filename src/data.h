#ifndef DATA_H
#define DATA_H

#include <vector>
#include "tree_utils.h"
#include <string>
#include <functional>
#include <sstream>

/**
 * Converte um caractere para minúsculo, se for uma letra maiúscula.
 * @param c Caractere a ser convertido.
 * @return Caractere convertido para minúsculo, se aplicável.
 */
char to_lower(char c);

/**
 * Processa uma string de texto, convertendo para minúsculas e removendo caracteres não alfanuméricos.
 * @param text Texto de entrada.
 * @return Vetor de palavras limpas e normalizadas extraídas do texto.
 */
std::vector<std::string> process_words(const std::string& text);

/**
 * Carrega documentos de um diretório e associa um ID a cada um.
 * Espera arquivos com nomes sequenciais (0.txt, 1.txt, ..., n.txt).
 * @param dir Caminho do diretório contendo os arquivos.
 * @param n_docs Número de documentos a serem carregados.
 * @return Vetor de pares contendo o conteúdo do documento e seu ID.
 */
std::vector<std::pair<std::string, int>> load_documents(const std::string& dir, int n_docs);

/**
 * Indexa uma coleção de documentos utilizando uma árvore binária e uma função de inserção.
 * Cada palavra processada é inserida na árvore com o ID do documento correspondente.
 * @param tree Ponteiro para a árvore binária.
 * @param docs Vetor de pares (conteúdo, ID) representando os documentos.
 * @param insert_function Função de inserção a ser usada (ex: AVL::insert).
 * @return Vetor com os resultados das inserções (tempo e número de comparações).
 */
std::vector<InsertResult> index_documents(BinaryTree* tree, const std::vector<std::pair<std::string, int>>& docs,
                     std::function<InsertResult(BinaryTree*, const std::string&, int)> insert_function);

#endif