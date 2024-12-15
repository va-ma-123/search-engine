#include "inverted_index.h" 
#include <sstream>
#include <algorithm>
#include <iostream>

// implement function to add document to index
void InvertedIndex::addDocument(int docId, const std::string& content) {
    std::istringstream stream(content);
    std::string word;

    // keep track of the number of terms in a document
    int docLength = 0;

    std::cout << "enter addDocument function" << std::endl;

    // Need a vector to store all the threads for parallel execution
    std::vector<std::thread> threads; 

    while (stream >> word) {
        // make all the words lower case so we have case-insensitive indexing
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // process words in parallel 
        // launch new threads for each word
        std::cout << "call processWord function for word: " << word << std::endl;
        threads.push_back(std::thread(&InvertedIndex::processWord, this, docId, word));
        // this->processWord(docId, word);
        docLength++;
    }

    // now join all the threads to ensure they're completed before proceeding
    for( auto& t : threads) {
        t.join();
        std::cout << "done processWord function" << std::endl;
    }

    { 
        std::lock_guard<std::mutex> lock(docLengths_mutex);
        docLengths[docId] = docLength;
    }
    totalDocs++;
    std::cout << "exit addDocument function" << std::endl;
}

std::unordered_map<int, int>& InvertedIndex::searchTerm(const std::string& term) const {
    std::cout << "enter searchTerm function with word: " << term << std::endl;
    // std::lock_guard<std::mutex> lock(index_mutex);
    // std::cout << "enter searchTerm function with word: " << term << std::endl;
    auto it = index.find(term);
    if (it != index.end()) {
        return it -> second;
    }
    // thread local static empty map to avoid thread-safety issues
    std::unordered_map<int, int> empty_map;
    std::cout << "exit searchTerm function" << std::endl;
    return empty_map;
}

void InvertedIndex::computeIDF(const std::string& term) {
    std::lock_guard<std::mutex> lock(index_mutex);
    std::cout << "enter computeIDF function for word: " << term << std::endl;
    auto it = index.find(term);
    if (it != index.end()){
        double idf = log((totalDocs - it->second.size() + 0.5) / (it->second.size() + 0.5) + 1.0);
        idfValues[term] = idf;
    }
    std::cout << "exit computeIDF function" << std::endl;
}

void InvertedIndex::processWord(int docId, const std::string& word) {
    std::lock_guard<std::mutex> lock(index_mutex); // lock this for thread safety
    std::cout << "enter processWord function for word: "  << word << std::endl;
    
    // get map of docId : freq for word
    std::cout << "calling searchTerm for word: "  << word << std::endl;
    std::unordered_map<int, int>& docToFreq = this->searchTerm(word);
    std::cout << "finished searchTerm call for word: "  << word << std::endl;
    std::cout << "docToFreq map size: " << docToFreq.size() << std::endl; // Check map size
    auto it = docToFreq.find(docId);
    if( it != docToFreq.end()) {
        // if word already has docId in its map, add 1 to the frequency
        it -> second++;
        std::cout << "Updated frequency for docId: " << docId << ", word: " << word << std::endl;
    } else {
        // if docId is not in the word's map, add to the map, with frequency value 1
        docToFreq[docId] = 1;
        std::cout << "Added docId: " << docId << " with frequency 1 for word: " << word << std::endl;
    }
    std::cout << "exit processWord function" << std::endl;
}
