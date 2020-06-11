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

    #ifdef STATIC_SEARCH
    
    void NodeContainer::build() {
        std::sort((this->docs).begin(), (this->docs).end(), std::greater<NodeValue>());
    }

    #endif 
};