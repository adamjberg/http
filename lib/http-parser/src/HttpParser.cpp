//
// Created by adam on 05/02/17.
//

#include "HttpParser.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>

HttpParser::HttpRequest HttpParser::parseRequest(const std::string &requestString) {
    unsigned startIndex = 0;
    unsigned endIndex = 0;

    HttpRequest req;
    std::string currentHeaderKey;

    bool endLine = false;
    bool headersDone = false;
    bool firstLine = true;

    while(endIndex < requestString.size()) {
        char c = requestString[endIndex];

        if(headersDone) {
            req.body = requestString.substr(endIndex, requestString.size() - endIndex);
            break;
        }

        if(c == ':') {
            currentHeaderKey = requestString.substr(startIndex, endIndex - startIndex);
            startIndex = endIndex + 2;
        }

        if(c == '\r') {
            if(firstLine) {
                std::string line = requestString.substr(startIndex, endIndex - startIndex);
                unsigned currentPos = 0;
                size_t spacePos = line.find(' ');
                while(spacePos < line.size()) {
                    if(req.method.size() == 0) {
                        req.method = line.substr(currentPos, spacePos - currentPos);
                    }
                    else if(req.path.size() == 0) {
                        req.path = line.substr(currentPos, spacePos - currentPos);
                        firstLine = false;
                        break;
                    }

                    currentPos = spacePos + 1;
                    spacePos = line.find(' ', currentPos);
                }
            }
            else {
                req.headers[currentHeaderKey] = requestString.substr(startIndex, endIndex - startIndex);
            }
        }
        else if(c == '\n') {
            if(endLine) {
                headersDone = true;
            }

            endLine = true;
            startIndex = endIndex + 1;
        }
        else {
            endLine = false;
        }

        endIndex++;
    }

    return std::move(req);
}

std::string HttpParser::GetResponseString(const HttpParser::HttpResponse &response) {
    std::ostringstream ss;

    ss << "HTTP/1.1 ";
    ss << response.status;
    ss << "\r\n";
    ss << "\r\n";

    ss << response.body;

    std::cout << ss.str();

    return ss.str();
}

