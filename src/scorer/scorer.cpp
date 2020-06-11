#include "scorer/scorer.hpp"

namespace scorer {
    Scorer::Scorer(folly::F14FastMap<std::string, std::string> *documents) {
        this->documents = documents;
    }
    Scorer::~Scorer() {

    }
};