#ifndef EDGE_HPP
#define EDGE_HPP
#include <folly/AtomicHashmap.h>
#include "fst/node.hpp"


namespace fst {
    class Edge {
        public:
            Edge(fst::Node *to);
            ~Edge();
            fst::Node *to;
            folly::AtomicHashMap<char, fst::Edge *> *getEdgeMap();
    };
};

#endif //EDGE_HPP