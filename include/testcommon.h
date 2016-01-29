#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include <string>
#include "log.h"

/**
 * \namespace Test
 * \brief A collection of utility functions for unit testing.
 */
namespace Test {

/**
 * Log a message to certain location(s).
 *
 * As much as possible, testers should use the log_* functions, so that
 * statements are all logged to the same file/stream.
 *
 * \param msg String to log
 */
void log_msg(std::string msg);

/**
 * Log the start of a test.
 *
 * \param id Short test identifier (string)
 * \param desc Test description/explanation
 */
void log_test(std::string id, std::string desc);

/**
 * Log a note/message about the current test.
 *
 * \param msg Message to log
 */
void log_test_note(std::string msg);

/**
 * Initialise testing.
 *
 * \return always returns 0 for now
 */
int init_tests();

} // namespace Test

#endif // TESTCOMMON_H
