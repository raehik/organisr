#include "log.h"
#include <iostream>

bool verbose = false;

void log(std::string msg) {
    if (verbose) {
        std::cout << msg << std::endl;
    }
}

void log(std::string pre, std::string msg) {
    if (verbose) {
        std::string msg_with_pre = pre + ": " + msg;
        log(msg_with_pre);
    }
}
