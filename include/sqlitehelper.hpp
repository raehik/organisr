#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <sqlite3.h>
#include <string>


/**
 * A wrapper for SQLite functions.
 */
class SQLiteHelper {
    public:
        SQLiteHelper();
        ~SQLiteHelper();
        int init_sqlite_db();

    private:
        std::string db_name;
        sqlite3 *db;
        static int callback(void *unused, int argc, char **argv, char **az_col_name);
        void log_msg(std::string message);
        void log_err(std::string message);
        bool file_exists(std::string filename);
};

#endif // SQLITEHELPER_H
