//
// Created by adam on 05/02/17.
//

#ifndef HTTP_SERVER_CONNECTION_H
#define HTTP_SERVER_CONNECTION_H


#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include "IMiddleware.h"


class Connection {
public:
    Connection(boost::asio::io_service &ioService, const IMiddleware *router, boost::asio::ip::tcp::socket socket);

    void do_write(boost::asio::yield_context yield);

    void do_read(boost::asio::yield_context yield);

    void handle_new_connection(boost::asio::yield_context yield);

    boost::asio::ip::tcp::socket socket;
    boost::asio::io_service &ioService;
    std::array<char, 8192> requestBuffer;
    const IMiddleware* router;
};

#endif //HTTP_SERVER_CONNECTION_H
