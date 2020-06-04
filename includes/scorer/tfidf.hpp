#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include "scorer/scorer.hpp"

namespace scorer {
    class TFIDFScorer : public Scorer {
        public:
            TFIDFScorer();
            ~TFIDFScorer();
    };
};


#endif // TF_IDF_HPP