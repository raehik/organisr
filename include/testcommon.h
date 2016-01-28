#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include <string>
#include "log.h"

namespace Test {

void log_msg(std::string);
void log_test(std::string, std::string);
void log_test_note(std::string);
int init_tests();

} // namespace Test

#endif // TESTCOMMON_H
