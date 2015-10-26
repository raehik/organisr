#include "sqlitehelper.hpp"
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
SQLiteHelper::SQLiteHelper(std::string db_file) {
    this->db_file = db_file;

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

    // run some tests
    step_api_test();
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
            "id          int  primary key not null," \
            "title       text             not null," \
            "description text);";

    //log_msg(sql_init);

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

    rc = sqlite3_exec(db, statements.c_str(), callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        log_err("SQL error: " + std::string(err_msg));
        sqlite3_free(err_msg);
        return 1;
    } else {
        log_msg("exec_sql: operation successful");
    }

    log_msg("exec_sql: finished");
    return 0;
}

/**
 * SELECT callback function for sqlite3_exec().
 */
int SQLiteHelper::callback(void *unused, int argc, char **argv, char **az_col_name) {
    log_msg("CALLBACK START");
    for (int i = 0; i < argc; i++) {
        std::cout << az_col_name[i] << " = " << std::endl << argv[i] ? argv[i] : "null";
    }
    std::cout << std::endl;
    log_msg("CALLBACK END");
    return 0;
}

void SQLiteHelper::print_db() {
    log_msg("Database");
}

void SQLiteHelper::step_api_test() {
    char *err_msg;
    sqlite3_stmt *stmt;
    std::string *pzTest;

    std::string sql = "select * from " + db_appt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        log_msg("failed to prepare statement");
        log_msg(to_string(sqlite3_errmsg(db)));
        sqlite3_finalize(stmt);
        throw("error");
    }
    log_msg("statement prepared successfully");

    do {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            log_msg(to_string(sqlite3_column_text(stmt, 0)));
            log_msg(to_string(sqlite3_column_text(stmt, 1)));
            log_msg(to_string(sqlite3_column_text(stmt, 2)));
        }
    } while (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
}
