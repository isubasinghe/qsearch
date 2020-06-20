

#include <iostream>
#include <folly/container/F14Map.h>
#include "docman/manager.hpp"
#include "fst/fst.hpp"

int main(int argc, char *argv[]) {
    docman::Manager manager;
    manager.insertDocument("why am i even here, idk idk");
    manager.insertDocument("jaberwocky idk idk");
    manager.insertDocument("idk who i am even anymore");
    return 0;
}