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
        this->edgeMap = new folly::F14FastMap<char, fst::Edge *>(36);
        this->nodeContainer = new NodeContainer();
    }
    bool Node::insert(std::string id, double score) {
        return this->nodeContainer->insert(id, score);
    }

    scoreIteratorPair Node::getIterator() {
        return std::make_tuple(this->nodeContainer->docs.begin(), this->nodeContainer->docs.end());
    }

    Node::~Node() {
        delete this->edgeMap;
    }
};