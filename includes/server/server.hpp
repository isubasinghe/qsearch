#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <memory>

#include "oatpp/network/server/ConnectionHandler.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/server/Server.hpp"
#include "oatpp/network/ConnectionProvider.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"

#define DEFAULT_QSEARCH_PORT 8080

namespace server {
    class Server {
        private:
            std::shared_ptr<oatpp::web::server::HttpRouter> *router = nullptr;
            oatpp::network::ServerConnectionProvider *serverConnectionProvider = nullptr;
            std::shared_ptr<oatpp::network::server::ConnectionHandler> *connectionHandler = nullptr;
        public:
            Server(unsigned short port);
            Server();
            void build();
            ~Server();
    };
};

#endif // SERVER_HPP