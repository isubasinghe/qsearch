#ifndef NODE_HPP
#define NODE_HPP

#include <folly/AtomicHashmap.h>



namespace fst {
    class Edge;

    class Node {
    private:
        bool finalNode;
        folly::AtomicHashMap<char, fst::Edge *> *edgeMap;
        char value;
    public:
        Node(bool finalNode, char value);
        ~Node();
        void addEdge(char value, Node *next);
    };   
};

#endif // NODE_HPP