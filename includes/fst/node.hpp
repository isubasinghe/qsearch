#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <folly/AtomicHashmap.h>
#include <mutex>
#include <shared_mutex>



namespace fst {
    class Edge;

    typedef struct NodeValue {
        NodeValue(std::string id, double scr): docId(id), score(scr){}

        #ifndef STATIC_SEARCH
        NodeValue *parent, *left, *right;
        unsigned long long balance;
        
        #endif //STATIC_SEARCH


        std::string docId;
        double score;
        bool operator > (const NodeValue& other) const {
            return (score > other.score);
        }
    } NodeValue;

    class NodeContainer {
        private:
            #ifdef STATIC_SEARCH
            std::vector<NodeValue> docs;
            #else
            mutable std::shared_mutex mutex;
            #endif // STATIC_SEARCH
        public:
            bool insert(std::string id, double score);
            std::vector<NodeValue> topK(unsigned long long k);
            #ifdef STATIC_SEARCH
            // Sort the array after all values have been inserted
            void build();
            #else
            bool updateScore(std::string id, double score);
            #endif // STATIC_SEARCH
    };

    class Node {
    private:
        NodeContainer *nodeContainer = nullptr;
        folly::AtomicHashMap<char, fst::Edge *> *edgeMap;
        char value;
    public:
        Node(bool finalNode, char value);
        ~Node();
        void addEdge(char value, Node *next);
    };   
};

#endif // NODE_HPP