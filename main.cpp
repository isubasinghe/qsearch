

#include <iostream>
#include <folly/container/F14Map.h>
#include "docman/manager.hpp"
#include "fst/fst.hpp"

int main(int argc, char *argv[]) {
    fst::FST *fst = new fst::FST();




    delete fst;
    return 0;
}