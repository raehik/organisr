#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include "dbobject.h"
#include "sqlitehelper.h"
#include "log.h"

using namespace Util;

std::string log_file_name = "digi-org-log.txt";

void log_msg(std::string msg) {
    std::ofstream log_file;
    log_file.open(log_file_name.c_str(), std::ios::app);
    log_file << msg << std::endl;
    log_file.close();
}

void log_test(std::string id, std::string desc) {
    log_msg("TEST" + id + " " + desc);
}

void log_test_note(std::string msg) {
    log_msg(msg);
}

// define shortcuts (function pointers)
void (*lt)(std::string, std::string) = log_test;
void (*ltn)(std::string) = log_test_note;

void test_sql() {
    remove("test-sql.db");
    lt("SQL00", "open new db file");
    SQLiteHelper db1("test-sql.db");

    lt("SQL01", "open existing db file");
    SQLiteHelper db2("test-sql.db");

    lt("SQL02", "check if a fake table exists");
    assert(! db2.table_exists("fake_table"));

    // TODO: how to make your own exceptions?
    // we only do one existence check because other insert/select functions all
    // use the same boilerplate table_exists() check code
    lt("SQL10", "select from non-existent table");
    std::vector<std::string> fake_cols;
    fake_cols.push_back("fake_col1");
    fake_cols.push_back("fake_col2");
    try {
        db2.select_columns_where("fake_table", fake_cols);
    } catch (SQLite::Exception e) {
        ltn(e.what());
    }

    lt("SQL11", "select from table with wrong columns");
    std::string sql_test = "create table table1(" \
            "id          integer  primary key," \
            "field       text);";
    db2.exec_sql(sql_test);
    try {
        db2.select_columns_where("table1", fake_cols);
    } catch (SQLite::Exception) {
        ltn(db2.get_errmsg());
    }

    lt("SQL13", "select from empty table");
    std::vector<std::string> t1_cols_id;
    t1_cols_id.push_back("id");
    t1_cols_id.push_back("field");
    std::vector< std::vector<DBObject> > res = db2.select_columns_where("table1", t1_cols_id);
    assert(res.size() == 0);

    lt("SQL20", "insert into table without id");
    std::vector<std::string> t1_cols;
    t1_cols.push_back("field");
    std::vector< std::vector<DBObject> > t1_rows;
    std::vector<DBObject> t1_row1;
    t1_row1.push_back(DBObject("ayy lmao"));
    t1_rows.push_back(t1_row1);
    try {
        db2.insert_rows("table1", t1_cols, t1_rows);
    } catch (SQLite::Exception e) {
        ltn(e.what());
    }

    lt("SQL21", "insert >1000 rows in one query");
    std::vector< std::vector<DBObject> > t1_huge_rows;
    std::vector<DBObject> row_tmp;
    for (int i = 0; i < 1000; i++) {
        row_tmp.clear();
        row_tmp.push_back(DBObject("ayy lmao"));
        t1_huge_rows.push_back(row_tmp);
    }
    std::stringstream ss;
    ss << t1_huge_rows.size();
    ltn("Number of rows to be added: " + ss.str());
    try {
        db2.insert_rows("table1", t1_cols, t1_huge_rows);
    } catch (SQLite::Exception e) {
        ltn(e.what());
    }
}

int start_sql_tests() {
    // delete log file if present from last time
    std::ifstream test_fin(log_file_name.c_str());
    if (test_fin) {
        remove(log_file_name.c_str());
        test_fin.close();
    }

    test_sql();
    return 0;
}
