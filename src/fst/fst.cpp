#include "fst/fst.hpp"


fst::FST::FST() {
    this->edgeMap = new folly::F14FastMap<char, fst::Edge *>(ALPHABET_SIZE);
}


fst::FST::~FST() {
    

    // Breadth first search to delete all edges;


    // Kepp track of all edges to delete
    std::vector<fst::Edge *> toDelete;

    // queue for breadth first search
    std::queue<folly::F14FastMap<char, fst::Edge *> *> queue;


    // initialise first level for breadth first search
    for (auto& x : *(this->edgeMap)) {
        folly::F14FastMap<char, fst::Edge *> *edgeMap = x.second->getEdgeMap();
        queue.push(edgeMap);
        fst::Edge *edge = (x.second);     
        toDelete.push_back(edge);
    }

    while(queue.size() > 0) {
        folly::F14FastMap<char, fst::Edge *> *edgeMap = queue.front();
        queue.pop();
        for (auto& x : *edgeMap) {
            folly::F14FastMap<char, fst::Edge *> *edgeMap = x.second->getEdgeMap();
            queue.push(edgeMap);
            fst::Edge *edge = (x.second);     
            toDelete.push_back(edge);
        }
    }

    for(auto edge: toDelete) {
        delete edge;
    }

    delete this->edgeMap;
}


bool fst::FST::addWord(std::string id, double score, std::string word) {
    std::cout << id << "\t" << score << "\t" << word << std::endl;
    folly::F14FastMap<char, fst::Edge *> *edgeMap = this->edgeMap;
    for(std::string::size_type i = 0; i < word.size(); i++) {
        bool finalNode = (i == word.size()-1);
        fst::Edge *currentEdge = nullptr;
        fst::Node *currentNode = nullptr;
        auto maybeValue = edgeMap->find(word[i]);
        if(maybeValue == edgeMap->end()) {
            currentNode = new fst::Node(finalNode, word[i]);
            fst::Edge *edge = new fst::Edge(currentNode);
            currentEdge = edge;
            edgeMap->insert(std::make_pair(word[i], edge));
        }else {
            currentEdge = maybeValue->second;
            currentNode = currentEdge->to;
        }
        if(finalNode) {
            currentNode->insert(id, score);
        }
        edgeMap = currentEdge->getEdgeMap();
    }
    return true;
}

fst::scoreIteratorPair fst::FST::getIterator(std::string word) {
    folly::F14FastMap<char, fst::Edge *> *edgeMap = this->edgeMap;
    fst::Node *node = nullptr;
    std::set<fst::NodeValue, std::greater<fst::NodeValue>> fakeSet;

    for(std::string::size_type i = 0; i < word.size(); i++) {
        auto maybeValue = edgeMap->find(word[i]);
        if(maybeValue == edgeMap->end()) {
            return std::make_tuple(fakeSet.begin(), fakeSet.end());
        }
        node = maybeValue->second->to;
        auto pedge = maybeValue->second;
        edgeMap = pedge->getEdgeMap();
    }
    return node->getIterator();
}