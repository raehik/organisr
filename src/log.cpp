#include "log.h"
#include <iostream>

namespace Util {

bool verbose = true;

void log(std::string msg) {
    if (verbose) {
        std::cout << msg << std::endl;
    }
}

void log(std::string pre, std::string msg) {
    if (verbose) {
        log(pre + ": " + msg);
    }
}

void error(std::string msg) {
    std::cout << "ERROR: " + msg << std::endl;
}

void error(std::string pre, std::string msg) {
    error(pre + ": " + msg);
}

} // namespace util
