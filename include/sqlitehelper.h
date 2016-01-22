#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <iostream>
#include "dbhelper.h"
#include "dbobject.h"


/**
 * @brief A database wrapper for SQLite.
 */
class SQLiteHelper : public DBHelper {
    public:
        SQLiteHelper(std::string db_file);

        virtual int insert_rows(
                std::string table_name,
                std::vector<std::string> table_cols,
                std::vector< std::vector<DBObject> > rows);

        virtual std::vector< std::vector<DBObject> > select_columns_where(
                std::string table_name,
                std::vector<std::string> cols,
                std::string sql_where = "");

        ~SQLiteHelper();

        bool table_exists(std::string table);

        int exec_sql(std::string statement);

        std::string get_errmsg();

    private:
        SQLite::Database db;
        int open_db();

        static void log_msg(std::string message);
        static void log_err(std::string message);
        static bool file_exists(std::string filename);

        const static std::string SQL_PARAM;
};

#endif // SQLITEHELPER_H
