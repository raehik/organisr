#ifndef DBHELPER_H
#define DBHELPER_H

#include <string>
#include <vector>
#include "dbobject.h"

/**
 * \brief An abstract class defining methods for database helpers to implement.
 *
 * DBHelper is an abstract class (one that cannot be instantiated) which should
 * be inherited by specific database helpers (e.g. for SQLite).
 */
class DBHelper
{
public:
    DBHelper(std::string db_file);

    // empty virtual destructor for proper cleanup -- thanks Mr.C64,
    // http://stackoverflow.com/questions/12854778/abstract-class-vs-interface-in-c
    //virtual ~DBHelper() {}

    /**
     * \brief Insert up to 1000 rows into a specific table.
     *
     * Theoretically we shouldn't need to send columns in this function, since SQL
     * can query the columns for the specified table and check that the rows passed
     * fit it -- but I didn't know that when I wrote this :)
     *
     * \param table_name table name to insert into
     * \param table_cols table's columns
     * \param rows       information to insert
     * \return non-zero on error, else 0
     * \throw SQLite::Exception with a descriptive what() string in case of any
     *        errors
     */
    virtual int insert_rows(std::string table_name,
                             std::vector<std::string> table_cols,
                             std::vector< std::vector<DBObject> > rows) = 0;

    /**
     * \brief Select matching rows from a table using an optional 'where'
     *        clause.
     *
     * \param table_name table name to insert into
     * \param cols table's columns
     * \param sql_where information to insert
     * \return non-zero on error, else 0
     * \throw SQLite::Exception with a descriptive what() string in case of any
     *        errors
     * \return
     */
    virtual std::vector< std::vector<DBObject> > select_from_where(
            std::string table_name,
            std::vector<std::string> table_cols,
            std::string sql_where) = 0;

    void set_db_file(std::string db_file);
    std::string get_db_file();

protected:
    std::string db_file;
};

#endif // DBHELPER_H
