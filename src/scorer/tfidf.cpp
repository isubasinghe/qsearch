#include "scorer/tfidf.hpp"

namespace scorer {
    TFIDFScorer::TFIDFScorer(folly::F14FastMap<std::string, std::string> *documents, 
        folly::F14FastMap<std::string, unsigned long long> *wordFreqMap) : Scorer(documents, wordFreqMap) {

    }

    double TFIDFScorer::score(const std::string &word, unsigned long long termCount, unsigned long long docTermCount) {
        double tf = (termCount / (docTermCount + 1.0));
        double idf = log(((this->documents->size())/(*(this->wordFreqMap))[word]) + 1.0);
        double tfidf2 = tf * pow(idf, 2);
        return tfidf2;
    } 

    TFIDFScorer::~TFIDFScorer() {

    }
}