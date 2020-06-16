

#include <iostream>
#include <folly/container/F14Map.h>
#include "docman/manager.hpp"
#include "fst/fst.hpp"

int main(int argc, char *argv[]) {
    fst::FST *fst = new fst::FST();
    fst->addWord("1", "hello");
    fst->addWord("2", "how");
    fst->addWord("3", "hey");



    delete fst;
    return 0;
}