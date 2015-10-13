#include "sqlitehelper.hpp"
#include <iostream>
#include <stdio.h>

std::string SQLiteHelper::db_name = "test.db";
sqlite3 * SQLiteHelper::db;

/** \class SQLiteHelper
 *
 * A wrapper for SQLite functions.
 */
SQLiteHelper::SQLiteHelper() {
    int rc;

    // check if database file exists
    if (file_exists(db_name)) {
        log_msg("Database file exists, not initialising");
    } else {
        log_msg("Initialising database");
        init_sqlite_db();
    }
}

SQLiteHelper::~SQLiteHelper() {
    sqlite3_close(db);
}

void SQLiteHelper::log_msg(std::string message) {
    std::cout << message << std::endl;
}

bool SQLiteHelper::file_exists(std::string filename) {
    if (FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

int SQLiteHelper::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << argv[i] ? argv[i] : "NULL";
    }
    std::cout << std::endl;
    return 0;
}

/** Initialise the SQLite database file.
 *
 * Returns 1 if the database creation fails.
 */
int SQLiteHelper::init_sqlite_db() {
    char *err_msg = 0;
    int rc;
    std::string sql;

    // create database
    rc = sqlite3_open(db_name.c_str(), &db);

    // try to open database with sqlite
    if (rc) {
      log_msg("Can't open database: " + std::string(sqlite3_errmsg(db)));
      return 1;
    } else {
      log_msg("Opened database successfully");
    }

    // form SQL statement
    sql = "CREATE TABLE COMPANY(" \
            "ID INT PRIMARY KEY   NOT NULL," \
            "TITLE          TEXT  NOT NULL," \
            "DESCRIPTION    TEXT);";

    // now run it
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        log_msg("Table created successfully");
    }

    sqlite3_close(db);
    return 0;
}
