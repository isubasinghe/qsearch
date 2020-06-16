#ifndef EDGE_HPP
#define EDGE_HPP
#include <folly/AtomicHashmap.h>
#include "fst/node.hpp"


namespace fst {
    class Edge {
        private:
            fst::Node *to;
        public:
            
            Edge(fst::Node *to);
            ~Edge();
            folly::AtomicHashMap<char, fst::Edge *> *getEdgeMap();
    };
};

#endif //EDGE_HPP