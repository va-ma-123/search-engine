#include "bm25.h"
#include "inverted_index.h"
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <iostream>

BM25::BM25(const InvertedIndex& index, double k1, double b)
    : index(index), k1(k1), b(b) {}

std::vector<std::pair<int, double>> BM25::rankDocuments(const std::string& query) {
    std::unordered_map<int, double> docScores;
    std::cout << "enter rankDocuments function" << std::endl;
    std::istringstream stream(query);
    std::string term;
    
    while (stream >> term) {
        if(index.getIDFValues().count(term) == 0) continue;

        double idf = index.getIDFValues().at(term);
        const auto& docList = index.searchTerm(term);
        
        for (const auto& [docId, termFreq] : docList) {
            docScores[docId] += computeScore(docId, term, termFreq);
        }
    }

    // convert the map of docScores to a vector of pairs for sorting
    std::vector<std::pair<int, double>> rankedDocs(docScores.begin(), docScores.end());
    std::sort(rankedDocs.begin(), rankedDocs.end(), [](const auto& a, const auto& b) { 
        return a.second > b.second; 
    });
    std::cout << "exit rankDocuments function" << std::endl;
    return rankedDocs;
}

double BM25::computeScore(int docId, const std::string& term, int termFreq) const {
    double idf = index.getIDFValues().at(term);
    double docLen = index.getDocLengths().at(docId);
    double avgLen = 0.0;
    std::cout << "enter computeScore function" << std::endl;
    // calculate the average length
    for (const auto& [docId, len] : index.getDocLengths()) {
        avgLen += len;
    }
    if(index.getDocLengths().size() > 0) {
        avgLen /= index.getDocLengths().size();
    } else {
        avgLen = 1.0; // avoid division by 0
    }
    std::cout << "exit computeScore function" << std::endl;
    return idf *  (termFreq * (k1 + 1)) / (termFreq + k1 * (1 - b + b * (docLen / avgLen)));
}