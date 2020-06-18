#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <folly/AtomicHashmap.h>
#include <set>
#include <mutex>
#include <shared_mutex>

#include "fst/alphabet.hpp"


namespace fst {
    class Edge;

    typedef struct NodeValue {
        NodeValue(std::string id, double scr): docId(id), score(scr){}
        std::string docId;
        double score;
        bool operator > (const NodeValue& other) const {
            return (score > other.score);
        }
    } NodeValue;

    class NodeContainer {
        private:
            friend class Node;
            std::set<NodeValue, std::greater<NodeValue>> docs;
        public:
            bool insert(std::string id, double score);
    };

    class Node {
    private:
        NodeContainer *nodeContainer = nullptr;
        char value;
        bool finalNode;
    public:
        Node(bool finalNode, char value);
        ~Node();
        bool insert(std::string id, double score);
        std::set<fst::NodeValue, std::greater<fst::NodeValue>>::iterator getIterator();
        folly::AtomicHashMap<char, fst::Edge *> *edgeMap;
    };   
};

#endif // NODE_HPP