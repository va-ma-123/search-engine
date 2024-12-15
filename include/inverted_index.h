#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <unordered_map>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cmath>

class InvertedIndex {
public:
    // Add a document to the index
    void addDocument(int docId, const std::string& content);

    // Retrieve all the documents that contain a given term
    std::unordered_map<int, int>& searchTerm(const std::string& term) const;

    // Compute IDF value for a given term
    void computeIDF(const std::string& term);

    // helper method to process a word to add it to the index
    void processWord(int docId, const std::string& word);

    // Getter for document lengths
    const std::unordered_map<int, double>& getDocLengths() const { return docLengths; }

    // Getter for idf values
    const std::unordered_map<std::string, double>& getIDFValues() const { return idfValues; }

    // Getter for total number of documents
    int getTotalDocs() const { return totalDocs; }

private:
    // Map of map
    // key is string, value is map of doc Id: frequency
    mutable std::unordered_map<std::string, std::unordered_map<int, int>> index;

    // map of docId: length of document
    mutable std::unordered_map<int, double> docLengths;
    
    // map of term: idf of term
    mutable std::unordered_map<std::string, double> idfValues;
    int totalDocs = 0;

    // mutexes for thread safety
    mutable std::mutex index_mutex;
    mutable std::mutex docLengths_mutex;
};

#endif