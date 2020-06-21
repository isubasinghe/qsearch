

#include <iostream>
#include <folly/container/F14Map.h>
#include "docman/manager.hpp"
#include "fst/fst.hpp"

int main(int argc, char *argv[]) {
    docman::BatchInserter *batchInserter = new docman::BatchInserter();
    batchInserter->addDocument("1", "why am i even here, idk idk");
    batchInserter->addDocument("2", "jaberwocky idk idk");
    batchInserter->addDocument("3", "idk who i am even anymore");

    docman::Manager manager(batchInserter);

    delete batchInserter;

    return 0;
}