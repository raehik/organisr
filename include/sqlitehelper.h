#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <iostream>
#include "dbhelper.h"
#include "dataobject.h"
#include "datarecord.h"


/**
 * \brief A database wrapper for SQLite.
 */
class SQLiteHelper : public DBHelper
{
public:
    /**
     * \brief Initialise a SQLiteHelper.
     *
     * The SQLiteHelper class contains methods for manipulating a SQLite database.
     * It is used by DBHelper.
     *
     * \param db_file    The name of the SQLite database file to use.
     */
    SQLiteHelper(std::string db_file);

    // For the virtual functions, see DBHelper's documentation.
    virtual int insert_rows(
            std::string table_name,
            std::vector<std::string> table_cols,
            std::vector<DataRecord> rows);

    virtual std::vector<DataRecord> select_from_where(
            std::string table_name,
            std::vector<std::string> cols,
            std::string sql_where = "");

    /** \brief Delete a row in a table using its ID.
     *
     * \param table_name  table to use
     * \param id          id of row to delete
     *
     * \return 0 if success, else non-zero for a fail
     */
    int delete_from_where(
            std::string table_name,
            int id);

    /** \brief Update a single column in a row in a table using its ID.
     *
     * \param table_name  table to use
     * \param col         set col[0]=col[1]
     * \param id          id of row to update
     *
     * \return 0 if success, else non-zero for a fail
     * \throw SQLite::Exception if no such table or col.size() != 2
     */
    int update_id(
            std::string table_name,
            std::string where_col,
            DataObject where_val,
            int id);

    /**
     * \brief Deconstructor for SQLiteHelper.
     *
     * Used to do something though no longer, but I still require a non-default
     * deconstructor for SQLiteCPP to work.
     */
    ~SQLiteHelper();

    /**
     * \brief Check for the existence of a specified table.
     *
     * \param table name of table to check
     *
     * \return true is exists, false if doesn't
     * \throw rethrows any SQLite::Exception it catches
     */
    bool table_exists(std::string table);

    /**
     * \brief Execute a set of SQL statements.
     *
     * Just runs exec_sql() directly on the given string. Very dangerous, so any
     * object using a SQLiteHelper should only call exec_sql() with 'static'
     * strings i.e. nothing user input, since there's an easy possibility for
     * SQL injection.
     *
     * \return always returns 0
     * \throw SQLite::Exception in case of error
     */
    int exec_sql(std::string statement);

    /**
     * \brief Get the last SQL error message.
     *
     * \return the most recent error message from SQLiteCPP
     */
    std::string get_errmsg();

private:
    SQLite::Database db;

    /**
     * \brief Log a message.
     *
     * Now a wrapper for Util::log().
     *
     * \param message Message to log
     */
    static void log_msg(std::string message);

    /**
     * \brief Log an error.
     *
     * Now a wrapper for Util::error().
     *
     * \param message Error to log
     */
    static void log_err(std::string message);

    /**
     * \brief Check if a file exists.
     *
     * Currently unused, but I would be using it if I could be (SQLiteCPP forces you
     * to open the DB in the constructor, and it makes the file).
     */
    static bool file_exists(std::string filename);

    const static std::string SQL_PARAM;
};

#endif // SQLITEHELPER_H
