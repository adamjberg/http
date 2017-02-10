//
// Created by adam on 05/02/17.
//

#include <vector>
#include "StringUtils.h"

std::vector<std::string> StringUtils::Split(const std::string &str, const std::string &delim) {
    std::vector<std::string> values;
    unsigned startPos = 0;
    size_t delimPos = str.find(delim);
    while(delimPos < str.size()) {
        values.push_back(str.substr(startPos, delimPos - startPos));

        startPos = delimPos + 1;
        delimPos = str.find(delim, startPos);
    }


    return std::move(values);
}
