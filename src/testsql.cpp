#include "testsql.h"
#include <stdio.h>
#include "dataobject.h"
#include <fstream>
#include "sqlitehelper.h"
#include "testcommon.h"

using namespace Test;

int init_sql_tests() {
    return 0;
}

void test_sql() {
    init_sql_tests();
    remove("test-sql.db");
    log_test("SQL00", "open new db file");
    SQLiteHelper db_tmp("test-sql.db");

    log_test("SQL01", "open existing db file");
    SQLiteHelper db_test("test-sql.db");

    log_test("SQL02", "check if a fake table exists");
    assert(! db_test.table_exists("fake_table"));

    log_test("SQL03", "pass empty string to exec_sql()");
    db_test.exec_sql("");

    // we only do one existence check because other insert/select functions all
    // use the same boilerplate table_exists() check code
    log_test("SQL10", "select from non-existent table");
    std::vector<std::string> fake_cols;
    fake_cols.push_back("fake_col1");
    fake_cols.push_back("fake_col2");
    try {
        db_test.select_from_where("fake_table", fake_cols);
    } catch (SQLite::Exception e) {
        log_test_note(e.what());
    }

    // create main table
    std::string t1 = "table1"; // set main test table name
    std::string sql_test = "create table " + t1 + "(" \
            "id          integer  primary key," \
            "field       text);";
    db_test.exec_sql(sql_test);

    log_test("SQL11", "select from table with wrong columns");
    try {
        db_test.select_from_where(t1, fake_cols);
    } catch (SQLite::Exception) {
        log_test_note(db_test.get_errmsg());
    }

    log_test("SQL13", "select from empty table");
    std::vector<std::string> t1_cols_id;
    t1_cols_id.push_back("id");
    t1_cols_id.push_back("field");
    std::vector<DataRecord> res = db_test.select_from_where(t1, t1_cols_id);
    assert(res.size() == 0);

    log_test("SQL20", "insert into table without id");
    std::vector<std::string> t1_cols;
    t1_cols.push_back("field");
    std::vector<DataRecord> t1_rows;
    DataRecord t1_row1;
    t1_row1.add(DataObject("test"));
    t1_rows.push_back(t1_row1);
    try {
        db_test.insert_rows(t1, t1_cols, t1_rows);
    } catch (SQLite::Exception e) {
        log_test_note(e.what());
    }

    log_test("SQL21", "insert >1000 rows in one query");
    std::vector<DataRecord> t1_huge_rows;
    for (int i = 0; i < 1000; i++) {
        DataRecord row_tmp;
        row_tmp.add(DataObject("test"));
        t1_huge_rows.push_back(row_tmp);
    }
    std::stringstream ss;
    ss << t1_huge_rows.size();
    log_test_note("Number of rows to be added: " + ss.str());
    try {
        db_test.insert_rows(t1, t1_cols, t1_huge_rows);
    } catch (SQLite::Exception e) {
        log_test_note(e.what());
    }

    log_test("SQL22", "insert nothing into table");
    std::vector<DataRecord> t1_nanimo;
    try {
        db_test.insert_rows(t1, t1_cols, t1_nanimo);
    } catch (SQLite::Exception e) {
        log_test_note(e.what());
    }

    log_test("SQL23", "SQL injection attack");
    std::vector<DataRecord> t1_inject;
    DataRecord row_inject;
    row_inject.add(DataObject("Robert'); drop table " + t1 + ";"));
    t1_inject.push_back(row_inject);
    db_test.insert_rows(t1, t1_cols, t1_inject);
    std::vector<DataRecord> inject_select = db_test.select_from_where(t1, t1_cols);
    log_test_note("table " + t1 + " contents:");
    for (std::vector<DataRecord>::size_type i = 0; i != inject_select.size(); i++) {
        DataRecord tmp = inject_select[i];
        log_test_note(tmp.get_object(0).get_str());
    }
    assert(db_test.table_exists(t1));
}
