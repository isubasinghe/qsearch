#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include <folly/container/F14Map.h>
#include <iostream>

#include "scorer/scorer.hpp"

namespace scorer {
    class TFIDFScorer : public Scorer {
        public:
            TFIDFScorer(folly::F14FastMap<std::string, std::string> *documents);
            ~TFIDFScorer();
    };
};


#endif // TF_IDF_HPP