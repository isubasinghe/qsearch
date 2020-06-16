#include "fst/edge.hpp"


namespace fst {
    Edge::Edge(fst::Node *to) {
        this->to = to;
    }
    Edge::~Edge() {
        delete this->to;
    }
    folly::AtomicHashMap<char, fst::Edge *> *Edge::getEdgeMap() {
        return this->to->edgeMap;
    }
};