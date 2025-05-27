#include "data.h"
#include <iostream>
#include <fstream>
#include <filesystem>


namespace fs = std::filesystem;

std::vector<std::string> process_words(const std::string& text){
    std::istringstream stream(text);
    std::string word;
    std::vector<std::string> words;

    while (stream >> word) {
        std::transform(word.begin(),word.end(),word.begin(), 
                   [](unsigned char c){ return std::tolower(c); }); // deixa tudo em letra minúscula
        words.push_back(word);
    }
    return words;
}
// OBS: Não vai funcionar pois os arquivos ainda estão no .zip
std::vector<std::pair<std::string, int>> load_documents(const std::string& dir, int n_docs) {
    std::vector<std::pair<std::string, int>> documents;
    int count = 0;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir: " << entry.path() << "\n";
                continue;
            }

            std::string content((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());

            documents.emplace_back(content, count); // conteúdo e ID
            count++;

            if (count >= n_docs) break;
        }
    }

    return documents;
}

std::vector<InsertResult> index_documents(BinaryTree* tree, const std::vector<std::pair<std::string, int>>& docs,
                     std::function<InsertResult(BinaryTree*, const std::string&, int)> insert_function) {
    std::vector<InsertResult> results;
    for (const std::pair<std::string, int>& doc : docs) {
        std::vector<std::string> words = process_words(doc.first);
        for (const std::string& word : words) {
            results.push_back(insert_function(tree, word, doc.second));
        }
    }
    return results;
}

