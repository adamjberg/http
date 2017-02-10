//
// Created by adam on 05/02/17.
//

#ifndef HTTP_IMIDDLEWARE_H
#define HTTP_IMIDDLEWARE_H

#include <HttpRequest.h>
#include <HttpResponse.h>

class IMiddleware {
public:
    virtual void handle(HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) const = 0;
};

#endif //HTTP_IMIDDLEWARE_H
