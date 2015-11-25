#include "log.h"
#include <iostream>

void log(std::string msg) {
    std::cout << msg << std::endl;
}

void log(std::string pre, std::string msg) {
    std::string msg_with_pre = pre + ": " + msg;
    log(msg_with_pre);
}
