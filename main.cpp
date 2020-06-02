#include <iostream>
#include <folly/container/F14Map.h>
#include "docman/manager.hpp"

int main(int argc, char *argv[]) {
    
    docman::Manager m;
    std::string x = "Hello World, what is up?";
    m.insertDocument(x);
    return 0;
}