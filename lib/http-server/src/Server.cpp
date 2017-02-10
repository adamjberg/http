//
// Created by adam on 05/02/17.
//

#include "Server.h"
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

Server::Server(unsigned short port) : tcp_endpoint({tcp::v4(), port}),
                                      acceptSocket({ioService, tcp_endpoint}) {

}

void Server::Use(const IMiddleware *router) {
    this->router = router;
}

void Server::Run() {
    acceptSocket.listen();
    spawn(ioService, std::bind(&Server::Accept, this, std::placeholders::_1));
    ioService.run();
}

void Server::Accept(yield_context yield) {
    while (acceptSocket.is_open())
    {
        tcp::socket socket = tcp::socket(ioService);

        try {
            acceptSocket.async_accept(socket, yield);
        }
        catch (boost::system::system_error err) {
            std::cerr << "accept\n";
        }

        try {
            connections.emplace_back(ioService, router, std::move(socket));
        }
        catch (boost::system::system_error err) {
            std::cerr << "create connection\n";
        }
    }
}
