#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <sqlite3.h>
#include <string>


/**
 * A wrapper for SQLite functions.
 */
class SQLiteHelper {
    public:
        SQLiteHelper(std::string db_file);
        ~SQLiteHelper();

        int init_sqlite_db();
        void print_db();

    private:
        sqlite3 *db;
        std::string db_file;
        int exec_sql(std::string statement);
        int open_db();


        static std::string db_appt;

        static void log_msg(std::string message);
        static void log_err(std::string message);
        static int callback(void *unused, int argc, char **argv, char **az_col_name);
        static bool file_exists(std::string filename);
        template <typename T> static std::string to_string(T var);

        void step_api_test();
};

#endif // SQLITEHELPER_H
