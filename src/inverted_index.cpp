#include "inverted_index.h" 
#include <sstream>
#include <algorithm>

// implement function to add document to index
void InvertedIndex::addDocument(int docId, const std::string& content) {
    std::istringstream stream(content);
    std::string word;

    while (stream >> word) {
        // make all the words lower case so we have case-insensitive indexing
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // add document id to the term's list of ids
        index[word].push_back(docId);
    }
}

std::vector<int> InvertedIndex::searchTerm(const std::string& term) const {
    auto it = index.find(term);
    if (it != index.end()){
        return it->second;
    }
    return {};
}