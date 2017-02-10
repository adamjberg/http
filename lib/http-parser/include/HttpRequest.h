//
// Created by adam on 05/02/17.
//

#ifndef HTTP_HTTPREQUEST_H
#define HTTP_HTTPREQUEST_H

#include <string>
#include <map>
#include "HttpResponse.h"

namespace HttpParser {
    struct HttpRequest {
        std::string path;
        std::string method;
        std::string body;

        std::map<std::string, std::string> headers;
        std::string param;
    };
}

#endif //HTTP_HTTPREQUEST_H
