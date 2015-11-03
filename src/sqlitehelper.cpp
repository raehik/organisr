#include "sqlitehelper.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

std::string SQLiteHelper::db_appt = "appointments";

/**
 * @brief Initialise a SQLiteHelper.
 *
 * The SQLiteHelper class contains methods for manipulating a SQLite database.
 * It is used by DBHelper.
 *
 * @param db_file    The name of the SQLite database file to use.
 */
SQLiteHelper::SQLiteHelper(std::string db_file) : DBHelper(db_file) {
    // check if database file exists
    if (file_exists(this->db_file)) {
        log_msg("Database file exists -- not initialising");
    } else {
        log_msg("Initialising database");
        int rc = init_sqlite_db();
        if (rc != 0) {
            log_err("Something went wrong, init_sqlite_db returned " + to_string(rc));
        }
    }

    // connect to database
    open_db();
}

SQLiteHelper::~SQLiteHelper() {
    // close the database when helper ends
    // TODO: this may not be permanent
    sqlite3_close(db);
}

/**
 * Convert a variable to a string.
 */
template <typename T> std::string SQLiteHelper::to_string(T var) {
    std::stringstream stream;
    stream << var;
    return stream.str();
}

void SQLiteHelper::log_msg(std::string message) {
    std::cout << message << std::endl;
}

void SQLiteHelper::log_err(std::string message) {
    log_msg(message);
}

/**
 * Check if a file exists.
 */
bool SQLiteHelper::file_exists(std::string filename) {
    char * FILE_READ = (char *)"r";
    if (FILE *file = fopen(filename.c_str(), FILE_READ)) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

/**
 * Initialise the SQLite database file.
 *
 * @return      non-zero on fail, else 0
 */
int SQLiteHelper::init_sqlite_db() {
    char *err_msg = 0;
    int rc;
    std::string sql_init;

    // create database
    rc = sqlite3_open(db_file.c_str(), &db);

    // try to open database with sqlite
    if (rc) {
      log_err("can't open database: " + std::string(sqlite3_errmsg(db)));
      return 1;
    } else {
      log_msg("opened database successfully");
    }

    // form SQL statement
    sql_init = "create table appointments(" \
            "id          integer  primary key," \
            "title       text     not null," \
            "description text);";

    // now run it
    rc = exec_sql(sql_init);

    if (rc != 0) {
        log_err("error while executing init SQL");
        return 2;
    }

    return 0;
}

int SQLiteHelper::open_db() {
    int rc = sqlite3_open(db_file.c_str(), &db);
    if (rc == SQLITE_OK) {
        log_msg("opened database successfully");
        return 0;
    } else {
        log_msg("failed to open database");
        return 1;
    }
}

/**
 * Execute a set of SQL statements.
 *
 * @return      non-zero on fail, else 0
 */
int SQLiteHelper::exec_sql(std::string statements) {
    log_msg("exec_sql: beginning");
    char * err_msg = 0;
    int rc;

    rc = sqlite3_exec(db, statements.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        log_err("SQL error: " + std::string(err_msg));
        sqlite3_free(err_msg);
        return 1;
    } else {
        log_msg("exec_sql: operation successful");
    }

    log_msg("exec_sql: finished successfully");
    return 0;
}

void SQLiteHelper::print_db() {
    log_msg("Database");
}

void SQLiteHelper::insert_rows(
        std::string table_name,
        std::vector<std::string> table_cols,
        std::vector< std::vector<std::string> > rows)
{
    char *err_msg;
    sqlite3_stmt *stmt;
    char *pzTest;
    std::string cols_str;
    std::vector<std::string> cur_row;

    // see http://stackoverflow.com/q/452859/2246637
    if (rows.size() > 1000) {
        log_msg("ERROR: too many rows");
        // TODO: throw an exception
    }

    std::string sql = "insert into " + table_name + "(";
    for (std::vector<std::string>::size_type i = 0; i != table_cols.size(); i++) {
        if (i != 0) {
            cols_str += ",";
        }
        cols_str += table_cols[i];
    }
    sql += cols_str + ") values";

    // TODO: parameterise instead of inserting blindly
    for (std::vector< std::vector<std::string> >::size_type i = 0; i != rows.size(); i++) {
        if (i != 0) {
            sql += ",";
        }
        sql += "(";
        cur_row = rows[i];
        for (std::vector<std::string>::size_type j = 0; j != cur_row.size(); j++) {
            if (j != 0) {
                sql += ",";
            }
            sql += "\"" + cur_row[j] + "\"";
        }
        sql += ")";
    }

    log_msg(sql);
    exec_sql(sql);
}

std::vector< std::vector<std::string> > SQLiteHelper::select_columns_where(
        std::string table_name,
        std::vector<std::string> cols,
        std::string sql_where)
{
    char *err_msg;
    sqlite3_stmt *stmt;
    char *pzTest;
    std::string cols_str;
    std::vector<std::string> cur_record;
    std::vector< std::vector<std::string> > records;

    std::string sql;

    sql = "select ";

    for (std::vector<std::string>::size_type i = 0; i != cols.size(); i++) {
        if (i != 0) {
            sql += ",";
        }
        sql += cols[i];
    }

    sql += " from " + table_name;

    if (sql_where != "") {
        // TODO: parameterise
        sql += " where " + sql_where;
    }

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        log_msg("failed to prepare statement");
        log_msg(to_string(sqlite3_errmsg(db)));
        sqlite3_finalize(stmt);
        throw("error");
    }
    log_msg("statement prepared successfully");

    // package up all output info
    std::string tmp_str;
    do {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            for (int i = 0; i != cols.size(); i++) {
                tmp_str = to_string(sqlite3_column_text(stmt, i));
                log_msg("col: " + tmp_str);
                cur_record.push_back(tmp_str);
            }
            records.push_back(cur_record);
        }
    } while (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return records;
}
