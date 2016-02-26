#ifndef RECAPPT_H
#define RECAPPT_H

#include <string>

/**
 * \brief A utility class/struct to make storing/using appointments easier.
 *
 * Hopefully this will minimise incompatibilities caused by database schema
 * changes, since values will be accessed via variable names rather than
 * indices.
 */
struct RecAppt {
    int id;
    std::string title;
    std::string desc;
    int date;
    int time;
    std::string location;
};

#endif // RECAPPT_H
