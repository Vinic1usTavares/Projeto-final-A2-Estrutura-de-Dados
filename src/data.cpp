/**
 * @file data_processing.h
 * @brief Funções para processamento de texto e indexação de documentos em uma árvore binária.
 */

#include "data.h"
#include "tree_utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

/**
 * @brief Converte um caractere para minúscula.
 * @param c Caractere a ser convertido.
 * @return O caractere em minúscula, ou o próprio caractere se não for letra maiúscula.
 */
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

/**
 * @brief Processa um texto extraindo palavras limpas (somente letras e números em minúsculas).
 * @param text Texto de entrada a ser processado.
 * @return Vetor de strings contendo as palavras processadas.
 * @note Remove caracteres especiais e converte tudo para minúsculas.
 *       Exemplo: "Hello, World!" → ["hello", "world"]
 */
std::vector<std::string> process_words(const std::string& text) {
    std::vector<std::string> words;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        std::string clean_word;
        for (char c : word) {
            char lower_c = to_lower(c);
            if ((lower_c >= 'a' && lower_c <= 'z') || 
                (lower_c >= '0' && lower_c <= '9')) {
                clean_word += lower_c;
            }
        }
        if (!clean_word.empty()) {
            words.push_back(clean_word);
        }
    }
    return words;
}

/**
 * @brief Carrega documentos de um diretório.
 * @param dir Caminho do diretório contendo os arquivos.
 * @param n_docs Número máximo de documentos a carregar (arquivos devem ser nomeados como 0.txt, 1.txt, etc.).
 * @return Vetor de pares contendo:
 *         - Conteúdo do documento (string)
 *         - ID do documento (int)
 * @note Emite avisos para arquivos não encontrados e erro se nenhum documento for carregado.
 */
std::vector<std::pair<std::string, int>> load_documents(const std::string& dir, int n_docs) {
    std::vector<std::pair<std::string, int>> documents;
    int count = 0;

    for (int i = 0; i < n_docs; ++i) {
        std::string filename = std::to_string(i) + ".txt";
        std::string fullpath = dir + "/" + filename;
        
        std::ifstream file(fullpath);
        if (!file.is_open()) {
            std::cerr << "Aviso: Não encontrado - " << fullpath << "\n";
            continue;
        }

        std::string content(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        documents.emplace_back(content, i);
        count++;
    }

    if (documents.empty()) {
        std::cerr << "Erro: Nenhum documento encontrado. Verifique o diretório e padrão de nomes.\n";
    }
    
    return documents;
}

/**
 * @brief Indexa palavras de documentos em uma árvore binária.
 * @param tree Ponteiro para a árvore binária de destino.
 * @param docs Vetor de documentos (conteúdo + ID).
 * @param insert_function Função de inserção específica (ex: AVL::insert).
 * @return Vetor de resultados de inserção para cada palavra.
 * @details Processa cada palavra dos documentos e insere na árvore usando a função especificada.
 */
std::vector<InsertResult> index_documents(
    BinaryTree* tree,
    const std::vector<std::pair<std::string, int>>& docs,
    std::function<InsertResult(BinaryTree*, const std::string&, int)> insert_function
) {
    std::vector<InsertResult> results;
    for (const auto& doc : docs) {
        std::vector<std::string> words = process_words(doc.first);
        for (const std::string& word : words) {
            results.push_back(insert_function(tree, word, doc.second));
        }
    }
    return results;
}