

#include <iostream>
#include <folly/container/F14Map.h>
#include "docman/manager.hpp"
#include "fst/fst.hpp"

int main(int argc, char *argv[]) {
    docman::BatchInserter *batchInserter = new docman::BatchInserter();


    docman::Manager manager(batchInserter);
    std::string query = "hello are you";

    manager.search(query, 1);

    delete batchInserter;

    return 0;
}