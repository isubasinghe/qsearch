#ifndef FST_HPP
#define FST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <folly/AtomicHashmap.h>

#include "fst/edge.hpp"
#include "fst/node.hpp"
#include "fst/alphabet.hpp"


namespace fst {
    class FST {
        private:
            folly::AtomicHashMap<char, fst::Edge *> *edgeMap;
        public:
            FST();
            ~FST();
            bool addWord(std::string id, double score, std::string word);
    };
};

#endif // FST_HPP