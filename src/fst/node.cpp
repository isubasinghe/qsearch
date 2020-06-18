#include "fst/node.hpp"


namespace fst {

    bool NodeContainer::insert(std::string id, double score) {
        NodeValue value(id, score);
        this->docs.insert(value);
        return true;
    }
    
    Node::Node(bool finalNode, char value) {
        this->finalNode = finalNode;
        this->value = value;
        this->edgeMap = new folly::AtomicHashMap<char, fst::Edge *>(36);
    }
    bool Node::insert(std::string id, double score) {
        return this->nodeContainer->insert(id, score);
    }
    Node::~Node() {
        delete this->edgeMap;
    }
};