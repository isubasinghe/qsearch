#include "server/server.hpp"

namespace server {
    Server::Server(unsigned short port) {
        this->serverConnectionProvider = new oatpp::network::server::SimpleTCPConnectionProvider(port);
    }
    Server::Server() {
        this->serverConnectionProvider = new oatpp::network::server::SimpleTCPConnectionProvider(DEFAULT_QSEARCH_PORT);
    }

    void Server::build() {

    }

    Server::~Server() {

    }
};