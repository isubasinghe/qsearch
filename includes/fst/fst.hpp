#ifndef FST_HPP
#define FST_HPP
#include <iostream>

#include "fst/edge.hpp"
#include "fst/node.hpp"


namespace fst {

    class FST {
        private:
            fst::Node *head;
        public:
            FST();
            ~FST();
            bool addWord(std::string id,std::string word);
    };
};

#endif // FST_HPP