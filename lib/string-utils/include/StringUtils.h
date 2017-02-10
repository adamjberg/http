//
// Created by adam on 05/02/17.
//

#ifndef HTTP_STRINGUTILS_H
#define HTTP_STRINGUTILS_H

#include <string>
#include <vector>

namespace StringUtils {
    std::vector<std::string> Split(const std::string &str, const std::string &delim);
}

#endif //HTTP_STRINGUTILS_H
