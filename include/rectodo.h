#ifndef RECTODO_H
#define RECTODO_H

#include <string>

/**
 * \brief A utility class/struct to make storing/using to-dos easier.
 *
 * Hopefully this will minimise incompatibilities caused by database schema
 * changes, since values will be accessed via variable names rather than
 * indices.
 */
struct RecTodo {
    std::string text;
    int id;
    bool done;
};

#endif // RECTODO_H
