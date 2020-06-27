#ifndef FST_HPP
#define FST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <tuple>

#include <folly/container/F14Map.h>

#include "fst/edge.hpp"
#include "fst/node.hpp"
#include "fst/alphabet.hpp"


namespace fst {
    class FST {
        private:
            folly::F14FastMap<char, fst::Edge *> *edgeMap;
        public:
            FST();
            ~FST();
            bool addWord(std::string id, double score, std::string word);
            scoreIteratorPair getIterator(std::string word);
    };
};

#endif // FST_HPP