//
// Created by adam on 05/02/17.
//

#include "Connection.h"
#include "HttpRequest.h"
#include "HttpParser.h"

#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

Connection::Connection(boost::asio::io_service &ioService, const IMiddleware *router, boost::asio::ip::tcp::socket socket)
        : ioService(ioService), router(router), socket(std::move(socket)) {
    spawn(ioService, std::bind(&Connection::handle_new_connection, this, std::placeholders::_1));
}

void Connection::do_write(yield_context yield) {
    HttpParser::HttpRequest req = HttpParser::parseRequest(std::string(requestBuffer.begin(), requestBuffer.end()));
    HttpParser::HttpResponse res;
    router->handle(req, res);

    std::string data = HttpParser::GetResponseString(res);

    //std::string data = "HTTP-Version: HTTP/1.0 200 OK\r\n\r\n";
    try {
        async_write(socket, buffer(data), yield);
    }
    catch (boost::system::system_error e) {
        std::cerr << "write" << e.what() << std::endl;
        socket.close();
    }
}

void Connection::do_read(yield_context yield) {
    try {
        socket.async_read_some(buffer(requestBuffer), yield);
    }
    catch (boost::system::system_error e) {
        if (e.code() == error::eof && e.code() != boost::asio::error::operation_aborted) {
            std::cout << "closing\n";
            socket.close();
        }
    }
}

void Connection::handle_new_connection(yield_context yield) {
    while(socket.is_open()) {
        std::cout << "start connection\n";
        do_read(yield);
        do_write(yield);
        socket.close();
        std::cout << "end connection\n";
    }
}
