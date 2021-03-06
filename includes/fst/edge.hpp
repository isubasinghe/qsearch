#ifndef EDGE_HPP
#define EDGE_HPP
#include <folly/container/F14Map.h>
#include "fst/node.hpp"


namespace fst {
    class Edge {
        public:
            Edge(fst::Node *to);
            ~Edge();
            fst::Node *to;
            folly::F14FastMap<char, fst::Edge *> *getEdgeMap();
    };
};

#endif //EDGE_HPP