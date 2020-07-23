#ifndef SERVER_HPP
#define SERVER_HPP

#include <cpprest/asyncrt_utils.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>

namespace server {
    class Server {
        public:
            Server(utility::string_t url);
            ~Server();
            pplx::task<void>open();
            pplx::task<void>close();
            void handleGet(web::http::http_request message);
            void handlePost(web::http::http_request message);
            void handlePut(web::http::http_request message);
            void handleDelete(web::http::http_request message);
            void handleOptions(web::http::http_request message);
        private:
            web::http::experimental::listener::http_listener listener;
    };
};

#endif // SERVER_HPP