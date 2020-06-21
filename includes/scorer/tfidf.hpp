#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include <folly/container/F14Map.h>
#include <iostream>

#include "scorer/scorer.hpp"

namespace scorer {
    class TFIDFScorer : public Scorer {
        public:
            TFIDFScorer(folly::F14FastMap<std::string, std::string> *documents, 
                folly::F14FastMap<std::string, unsigned long long> *wordFreqMap);
            ~TFIDFScorer();
            double score(unsigned long long docCount, unsigned long long docAppearances, 
                    unsigned long long termCount, unsigned long long docTermCount);
            double score(const std::string &word, unsigned long long termCount, unsigned long long docTermCount);
    };
};


#endif // TF_IDF_HPP