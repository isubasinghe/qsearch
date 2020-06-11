#include "scorer/tfidf.hpp"

namespace scorer {
    TFIDFScorer::TFIDFScorer(folly::F14FastMap<std::string, std::string> *documents) : Scorer(documents) {

    }
    TFIDFScorer::~TFIDFScorer() {

    }
}