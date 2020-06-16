#include "fst/node.hpp"


namespace fst {

    bool NodeContainer::insert(std::string id, double score) {
        #ifdef STATIC_SEARCH
        NodeValue value(id, score);
        this->docs.push_back(value);
        #else 

        #endif // STATIC_SEARCH
        
        return true;
    }
    
    Node::Node(bool finalNode, char value) {
        this->finalNode = finalNode;
        this->value = value;
        this->edgeMap = new folly::AtomicHashMap<char, fst::Edge *>(36);
    }



    Node::~Node() {
        delete this->edgeMap;
    }

    #endif 
};