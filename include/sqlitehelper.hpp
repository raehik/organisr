#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <sqlite3.h>
#include <string>


class SQLiteHelper
{
public:
    SQLiteHelper();
    ~SQLiteHelper();
    int init_sqlite_db();

private:
    static std::string db_name;
    static sqlite3 *db;
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    void log_msg(std::string message);
    void log_err(std::string message);
    bool file_exists(std::string filename);
};

#endif // SQLITEHELPER_H
