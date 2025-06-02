#include "data.h"
#include "tree_utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Função manual para converter para minúsculas
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

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

std::vector<std::pair<std::string, int>> load_documents(const std::string& dir, int n_docs) {
    std::vector<std::pair<std::string, int>> documents;
    int count = 0;

    for (int i = 0; i < n_docs; ++i) {  // Agora começa em 0
        // Gera o nome do arquivo: 0.txt, 1.txt, ... 99.txt
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

        documents.emplace_back(content, i); // O ID é o próprio i
        //std::cout << "Carregado: " << filename << " (ID: " << i << ")\n";
        count++;
    }

    if (documents.empty()) {
        std::cerr << "Erro: Nenhum documento encontrado. Verifique o diretório e padrão de nomes.\n";
    }
    
    return documents;
}

std::vector<InsertResult> index_documents(BinaryTree* tree, const std::vector<std::pair<std::string, int>>& docs,
                     std::function<InsertResult(BinaryTree*, const std::string&, int)> insert_function) {
    std::vector<InsertResult> results;
    for (const auto& doc : docs) {
        std::vector<std::string> words = process_words(doc.first);
        for (const std::string& word : words) {
            results.push_back(insert_function(tree, word, doc.second));
        }
    }
    return results;
}
