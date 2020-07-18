

#include <iostream>
#include <folly/container/F14Map.h>
#include "server/server.hpp"

int main(int argc, char *argv[]) {
    oatpp::base::Environment::init();

    server::Server server;

    oatpp::base::Environment::destroy();
    return 0;
}