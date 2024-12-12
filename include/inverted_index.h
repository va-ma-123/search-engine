#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <unordered_map>
#include <vector>
#include <string>

class InvertedIndex {
public:
    // We need a method to add a document to the index
    void addDocument(int docId, const std::string& content);

    // We need a method to get all the documents that contain a term
    std::vector<int> searchTerm(const std::string& term) const;

private:
    // The data structure used is a map
    // Each term is a key, and the values are list of document IDs that contain the term
    std::unordered_map<std::string, std::vector<int>> index;
};

#endif