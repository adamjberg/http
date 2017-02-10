//
// Created by adam on 05/02/17.
//

#ifndef HTTP_HTTPRESPONSE_H
#define HTTP_HTTPRESPONSE_H

#include <string>
#include <map>

namespace HttpParser {
    struct HttpResponse {
        unsigned short status = 0;
        std::map<std::string, std::string> headers;
        std::string body;
    };
}

#endif //HTTP_HTTPRESPONSE_H
