#ifndef LOG_H
#define LOG_H

#include <string>
#include <sstream>

namespace Util
{

void log(std::string msg);
void log(std::string pre, std::string msg);
void error(std::string msg);
void error(std::string pre, std::string msg);

/**
 * Convert a variable of any type to a string.
 */
// have to declare in header: see http://stackoverflow.com/q/495021/2246637
template <typename T> std::string to_string(T var) {
    std::stringstream stream;
    stream << var;
    return stream.str();
}

} // namespace util

#endif // LOG_H
