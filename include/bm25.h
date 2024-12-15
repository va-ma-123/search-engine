#ifndef BM25_H
#define BM25_H

#include <unordered_map>
#include <string>
#include <vector>
#include "inverted_index.h"

class InvertedIndex;

class BM25 {
public:
    // constructor
    BM25(const InvertedIndex& index, double k1=1.5, double b=0.75);

    // function to rank documents based on the query
    std::vector<std::pair<int, double>> rankDocuments(const std::string& query);

    // helper function to compute BM25 score
    double computeScore(int docId, const std::string& term, int termFreq) const;

private:
    const InvertedIndex& index;
    double k1; // this is the Term Frequency Saturation parameter
    double b; // this is the Length Normalization parameter
};

#endif