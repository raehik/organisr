#include "testcommon.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "log.h"

namespace Test {

/**
 * File used to log things to in log_msg() and log_test().
 *
 * Change to anything (relative, absolute or random) depending on what is most
 * convenient.
 */
std::string log_file_name = "digi-org-log.txt";

void log_msg(std::string msg) {
    // open log file for appending
    std::ofstream log_file;
    log_file.open(log_file_name.c_str(), std::ios::app);

    // log to file
    log_file << msg << std::endl;
    log_file.close();

    // also log to stdout since it's helpful
    std::cout << msg << std::endl;
}

void log_test(std::string id, std::string desc) {
    log_msg("TEST," + id + ",'" + desc + "'");
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
    return 0;
}

} // namespace Test
