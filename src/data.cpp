#include "data.h"
#include "tree_utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Converte um caractere para minúsculo, se for uma letra maiúscula
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

// Processa uma string de texto e extrai apenas as palavras válidas (letras e dígitos em minúsculo)
std::vector<std::string> process_words(const std::string& text) {
    std::vector<std::string> words;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        std::string clean_word;
        for (char c : word) {
            char lower_c = to_lower(c);
            // Aceita apenas caracteres alfanuméricos minúsculos
            if ((lower_c >= 'a' && lower_c <= 'z') || 
                (lower_c >= '0' && lower_c <= '9')) {
                clean_word += lower_c;
            }
        }
        // Adiciona a palavra limpa ao vetor, se não estiver vazia
        if (!clean_word.empty()) {
            words.push_back(clean_word);
        }
    }
    return words;
}

// Carrega n_docs documentos do diretório especificado, retornando um vetor de pares (conteúdo, id)
std::vector<std::pair<std::string, int>> load_documents(const std::string& dir, int n_docs) {
    std::vector<std::pair<std::string, int>> documents;
    int count = 0;

    for (int i = 0; i < n_docs; ++i) {  // Itera de 0 até n_docs - 1
        std::string filename = std::to_string(i) + ".txt";  // Ex: "0.txt"
        std::string fullpath = dir + "/" + filename;
        
        std::ifstream file(fullpath);
        if (!file.is_open()) {
            std::cerr << "Aviso: Não encontrado - " << fullpath << "\n";
            continue;  // Pula arquivos inexistentes
        }

        // Lê todo o conteúdo do arquivo como uma string
        std::string content(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        documents.emplace_back(content, i);  // Associa o conteúdo ao seu ID (i)
        count++;
    }

    // Verifica se algum documento foi carregado
    if (documents.empty()) {
        std::cerr << "Erro: Nenhum documento encontrado. Verifique o diretório e padrão de nomes.\n";
    }
    
    return documents;
}

// Indexa as palavras de cada documento na árvore, usando a função de inserção fornecida
std::vector<InsertResult> index_documents(BinaryTree* tree, const std::vector<std::pair<std::string, int>>& docs,
                     std::function<InsertResult(BinaryTree*, const std::string&, int)> insert_function) {
    std::vector<InsertResult> results;
    for (const auto& doc : docs) {
        // Processa palavras do conteúdo do documento
        std::vector<std::string> words = process_words(doc.first);
        for (const std::string& word : words) {
            // Insere cada palavra com o ID do documento
            results.push_back(insert_function(tree, word, doc.second));
        }
    }
    return results;
}