#include "scorer/tfidf.hpp"

namespace scorer {
    TFIDFScorer::TFIDFScorer(folly::F14FastMap<std::string, std::string> *documents, 
        folly::F14FastMap<std::string, unsigned long long> *wordFreqMap) : Scorer(documents, wordFreqMap) {

    }

    double TFIDFScorer::score(unsigned long long docCount, unsigned long long docAppearances, 
            unsigned long long termCount, unsigned long long docTermCount) {
        double tf = (termCount / (docTermCount + EPSILON));
        double idf = log(docCount/(docAppearances + EPSILON));
        return tf * pow(idf, 2);        
    }

    double TFIDFScorer::score(const std::string &word, unsigned long long termCount, 
        unsigned long long docTermCount) {
        return this->score(this->documents->size(), (*(this->wordFreqMap))[word], termCount, docTermCount);
    } 

    TFIDFScorer::~TFIDFScorer() {

    }
}