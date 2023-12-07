#pragma once

#include <cerrno>
#include <cstddef>
#include <fstream>
#include <string>

std::string getIndexOf(std::ifstream &ifs, size_t idx, const std::string &defaultVal) {
    std::string ret;
    while (ifs) {
        ifs >> ret;
        if (idx == 0)
            break;
        else
            idx--;
    }
    return (idx == 0) ? ret : defaultVal;
}

std::string getNth(std::ifstream &ifs, int n) {
    std::string ret;
    while (ifs && n > 0) {
        ifs >> ret;
        n--;
    }
    return (n == 0) ? ret : "";
}

long getNthLong(std::ifstream &ifs, int n, long defaultVal) {
    std::string str = getNth(ifs, n);
    if (str.empty()) {
        return defaultVal;
    }
    char *endPtr;
    long ret = std::strtol(str.c_str(), &endPtr, 10);
    if (errno != 0 || endPtr == nullptr || *endPtr != '\0') {
        return defaultVal;
    }
    return ret;
}
