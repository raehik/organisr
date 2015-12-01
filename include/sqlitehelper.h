#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include "dbhelper.h"
#include <iostream>
#include "dbobject.h"


/**
 * @brief A database wrapper for SQLite.
 */
class SQLiteHelper : public DBHelper {
    public:
        SQLiteHelper(std::string db_file);
        ~SQLiteHelper();

        virtual int insert_rows(
                std::string table_name,
                std::vector<std::string> table_cols,
                std::vector< std::vector<DBObject> > rows);

        virtual std::vector< std::vector<DBObject> > select_columns_where(
                std::string table_name,
                std::vector<std::string> cols,
                std::string sql_where = "");

        int init_sqlite_db();
        void print_db();

    private:
        SQLite::Database db;
        int exec_sql(std::string statement);
        int open_db();

        static void log_msg(std::string message);
        static void log_err(std::string message);
        static bool file_exists(std::string filename);
        template <typename T> static std::string to_string(T var);

        void step_api_test();
        const static std::string SQL_PARAM;
};

#endif // SQLITEHELPER_H
