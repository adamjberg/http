//
// Created by adam on 05/02/17.
//

#ifndef HTTP_HTTPPARSER_H
#define HTTP_HTTPPARSER_H

#include <string>
#include <map>

#include "HttpRequest.h"


namespace HttpParser {
    HttpRequest parseRequest(const std::string &requestString);

    std::string GetResponseString(const HttpResponse &response);
}

#endif //HTTP_HTTPPARSER_H
