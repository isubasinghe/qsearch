

#include <iostream>
#include <memory>
#include <cpprest/uri.h>
#include "server/server.hpp"


std::unique_ptr<server::Server> serverHandle;

void onInitialise(const utility::string_t& address) {
    web::uri_builder uri(address);
    auto addr = uri.to_uri().to_string();
    serverHandle = std::unique_ptr<server::Server>(new server::Server(addr));
    serverHandle->open().wait();
    return;
}

void onShutdown() {
    serverHandle->close().wait();
    return;
}

int main(int argc, char *argv[]) {

    utility::string_t port = U("8080");
    
    if (argc == 2) {
        port = argv[1];
    }

    utility::string_t address = U("http://127.0.0.1:");
    address.append(port);

    onInitialise(address);

    std::string line;
    std::getline(std::cin, line);

    onShutdown();
    return 0;
}