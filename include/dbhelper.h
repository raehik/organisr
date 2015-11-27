#ifndef DBHELPER_H
#define DBHELPER_H

#include <string>
#include <vector>
#include "dbobject.h"

/**
 * @brief An abstract class defining methods for database helpers to implement.
 *
 * DBHelper is an abstract class (one that cannot be instantiated) which should
 * be inherited by specific database helpers (e.g. for SQLite).
 */
class DBHelper {
public:
    DBHelper(std::string db_file);

    // empty virtual destructor for proper cleanup -- thanks Mr.C64,
    // http://stackoverflow.com/questions/12854778/abstract-class-vs-interface-in-c
    //virtual ~DBHelper() {}

    virtual int insert_rows(std::string table_name,
                             std::vector<std::string> table_cols,
                             std::vector< std::vector<DBObject> > rows) = 0;

    virtual std::vector< std::vector<DBObject> > select_columns_where(
            std::string table_name,
            std::vector<std::string> cols,
            std::string sql_where) = 0;

    void set_db_file(std::string db_file);
    std::string get_db_file();

protected:
    std::string db_file;
};

#endif // DBHELPER_H
