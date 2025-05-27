#ifndef DATA_H
#define DATA_H

#include <vector>
#include "tree_utils.h"
#include <string>
#include <functional>
#include <sstream>
#include <cctype>


std::vector<std::string> process_words(const std::string& text);
std::vector<std::pair<std::string, int>> load_documents(const std::string& dir, int n_docs);
std::vector<InsertResult> index_documents(BinaryTree* tree, const std::vector<std::pair<std::string, int>>& docs,
                     std::function<InsertResult(BinaryTree*, const std::string&, int)> insert_function);

#endif
