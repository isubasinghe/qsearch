#include "scorer/scorer.hpp"

namespace scorer {
    Scorer::Scorer(folly::F14FastMap<std::string, std::string> *documents, 
        folly::F14FastMap<std::string, unsigned long long> *wordFreqMap) {
        this->documents = documents;
        this->wordFreqMap = wordFreqMap;
    }
    Scorer::~Scorer() {

    }
};