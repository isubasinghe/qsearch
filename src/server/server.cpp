#include "server/server.hpp"

namespace server {
    Server::Server(utility::string_t url): listener(url) {

        this->listener.support(web::http::methods::POST, std::bind(&Server::handlePost, this, std::placeholders::_1));
    }
    Server::~Server() {

    }

    pplx::task<void> Server::open() {
        return this->listener.open();
    }

    pplx::task<void> Server::close() {
        return this->listener.close();
    }

    void Server::handleGet(web::http::http_request message) {

    }
    void Server::handlePost(web::http::http_request message) {
        std::cout << message.to_string() << std::endl;
        message.reply(web::http::status_codes::OK,message.to_string());
        return;
    }
    void Server::handlePut(web::http::http_request message) {

    }
    void Server::handleDelete(web::http::http_request message) {

    }
    void Server::handleOptions(web::http::http_request message) {

    }
};