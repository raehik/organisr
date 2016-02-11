#ifndef LOG_H
#define LOG_H

#include <string>
#include <sstream>

/**
 * \namespace Util
 * \brief Utility functions for logging and debugging.
 */
namespace Util {

/**
 * \brief Log a message.
 *
 * Messages are of lower importance than errors, so will not be displayed if
 * verbosity is off.
 *
 * \param msg Message to log
 */
void log(std::string msg);

/**
 * \brief Log a message.
 *
 * Messages are of lower importance than errors, so will not be displayed if
 * verbosity is off.
 *
 * \param pre String to prepend to message
 * \param msg Message to log
 */
void log(std::string pre, std::string msg);

/**
 * \brief Log an error.
 *
 * Errors will display regardless of verbosity.
 *
 * \param msg Error message to log
 */
void error(std::string msg);


/**
 * \brief Log an error.
 *
 * Errors will display regardless of verbosity.
 *
 * \param pre String to prepend (e.g. relevant class or namespace)
 * \param msg Error message to log
 */
void error(std::string pre, std::string msg);

/**
 * Convert a variable of any type to a string.
 */
// have to define in header: see http://stackoverflow.com/q/495021/2246637
template <typename T> std::string to_string(T var) {
    std::stringstream stream;
    stream << var;
    return stream.str();
}

} // namespace Util

#endif // LOG_H
