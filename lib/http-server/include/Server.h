//
// Created by adam on 05/02/17.
//

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <list>
#include "Connection.h"
#include "IMiddleware.h"

class Server {
public:
    Server(unsigned short port);

    void Use(const IMiddleware *router);

    void Run();

    void Accept(boost::asio::yield_context yield);

    boost::asio::io_service ioService;
    boost::asio::ip::tcp::endpoint tcp_endpoint;
    boost::asio::ip::tcp::acceptor acceptSocket;
    std::list<Connection> connections;

    const IMiddleware *router;
};

#endif //HTTP_SERVER_H
