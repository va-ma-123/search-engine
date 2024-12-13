#include "inverted_index.h" 
#include <sstream>
#include <algorithm>
#include <iostream>

// implement function to add document to index
void InvertedIndex::addDocument(int docId, const std::string& content) {
    std::istringstream stream(content);
    std::string word;

    // Need a vector to store all the threads for parallel execution
    std::vector<std::thread> threads; 

    while (stream >> word) {
        // make all the words lower case so we have case-insensitive indexing
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // process words in parallel 
        // launch new threads for each word
        threads.push_back(std::thread(&InvertedIndex::processWord, this, docId, word));
    }

    // now join all the threads to ensure they're completed before proceeding
    for( auto& t : threads) {
        t.join();
    }
}

void InvertedIndex::processWord(int docId, const std::string& word) {
    std::lock_guard<std::mutex> lock(index_mutex); // lock this for thread safety
    index[word].push_back(docId); // add document id to the term's list of ids
}

std::vector<int> InvertedIndex::searchTerm(const std::string& term) const {
    std::lock_guard<std::mutex> lock(index_mutex);
    auto it = index.find(term);
    if (it != index.end()){
        return it->second; // return all document id's that contain the term
    }
    return {}; // return empty vector if not found
}