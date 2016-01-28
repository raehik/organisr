#include "testcommon.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "log.h"

namespace Test {

std::string log_file_name = "digi-org-log.txt";

void log_msg(std::string msg) {
    std::ofstream log_file;
    log_file.open(log_file_name.c_str(), std::ios::app);
    log_file << msg << std::endl;
    log_file.close();

    // also log to stdout
    std::cout << msg << std::endl;
}

void log_test(std::string id, std::string desc) {
    log_msg("TEST [" + id + "] " + desc);
}

void log_test_note(std::string msg) {
    log_msg(msg);
}

int init_tests() {
    // delete log file if present from last time
    std::ifstream test_fin(log_file_name.c_str());
    if (test_fin) {
        remove(log_file_name.c_str());
        test_fin.close();
    }
}

} // namespace Test
