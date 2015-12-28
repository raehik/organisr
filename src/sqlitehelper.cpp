#include "sqlitehelper.h"

#include <stdio.h>
#include "log.h"

using namespace Util;

const std::string SQLiteHelper::SQL_PARAM = "?";

/**
 * @brief Initialise a SQLiteHelper.
 *
 * The SQLiteHelper class contains methods for manipulating a SQLite database.
 * It is used by DBHelper.
 *
 * @param db_file    The name of the SQLite database file to use.
 */
SQLiteHelper::SQLiteHelper(std::string db_file)
try : DBHelper(db_file), db(db_file, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE) {
    // in the member init list we tried to *open* the file -- if it succeeds
    // then this is all run, so pretend that the database is open
    log_msg("opened database successfully");
    std::string appt_table = "appointments";
    try {
        if (db.tableExists(appt_table)) {
            log_msg("table exists");
        } else {
            log_msg("table does not exist");
            init_sqlite_db();
        }
    } catch(SQLite::Exception e) {
        log_err("exception when checking for appt. table existence");
    }
}
catch(SQLite::Exception e) {
    log_err("SQLite database open or creation failed");

    // just throw e again after catching it lol
    throw e;
}

void SQLiteHelper::log_msg(std::string message) {
    log("SQLiteHelper: " + message);
}

void SQLiteHelper::log_err(std::string message) {
    error("SQLiteHelper: " + message);
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
    std::string sql_init;

    // form SQL statement
    sql_init = "create table appointments(" \
            "id          integer  primary key," \
            "title       text     not null," \
            "description text);";

    // now run it
    exec_sql(sql_init);

    return 0;
}

int SQLiteHelper::open_db() {
    // for now, we are forced to open the database in the constructor, so this
    // does nothing
    return 0;
}

/**
 * Execute a set of SQL statements.
 *
 * @return      non-zero on fail, else 0
 */
int SQLiteHelper::exec_sql(std::string statement) {
    log_msg("exec: " + statement);
    db.exec(statement);
    return 0;
}

void SQLiteHelper::print_db() {
    log_msg("Database");
}

int SQLiteHelper::insert_rows(
        std::string table_name,
        std::vector<std::string> table_cols,
        std::vector< std::vector<DBObject> > rows)
{
    std::string cols_str;
    std::vector<DBObject> cur_row;

    // see http://stackoverflow.com/q/452859/2246637
    if (rows.size() > 1000) {
        log_err("too many rows");
        // TODO: throw an exception
        return 1;
    }

    // columns
    std::string sql = "insert into " + table_name + "(";
    for (std::vector<DBObject>::size_type i = 0; i != table_cols.size(); i++) {
        if (i != 0) {
            cols_str += ",";
        }
        cols_str += table_cols[i];
    }
    sql += cols_str + ") values";

    // value placeholders (for binding later)
    for (std::vector< std::vector<DBObject> >::size_type i = 0; i != rows.size(); i++) {
        if (i != 0) {
            sql += ",";
        }
        sql += "(";
        cur_row = rows[i];
        for (std::vector<DBObject>::size_type j = 0; j != cur_row.size(); j++) {
            // as long as not first item, put a comma
            if (j != 0) { sql += ","; }
            sql += SQL_PARAM;
        }
        sql += ")";
    }

    log_msg("compiling SQL query");
    SQLite::Statement query(db, sql);

    // note that SQL parameters are counted starting from 1, not 0
    log_msg("binding values");
    int bind_count = 1;
    for (std::vector< std::vector<DBObject> >::size_type i = 0; i != rows.size(); i++) {
        for (std::vector<DBObject>::size_type j = 0; j != cur_row.size(); j++) {
            DBObject obj = rows[i][j];
            if (obj.type() == "string") {
                query.bind(bind_count, obj.get_str());
            } else if (obj.type() == "int") {
                query.bind(bind_count, obj.get_int());
            } else {
                error("DBObject of a type we can't handle");
                return 1;
            }

            bind_count++;
        }
    }
    query.exec();
    return 0;
}

std::vector< std::vector<DBObject> > SQLiteHelper::select_columns_where(
        std::string table_name,
        std::vector<std::string> cols,
        std::string sql_where)
{
    std::vector<DBObject> cur_record;
    std::vector< std::vector<DBObject> > records;

    std::string sql;

    // start the query
    sql = "select ";

    // select specified columns
    for (std::vector<std::string>::size_type i = 0; i != cols.size(); i++) {
        if (i != 0) {
            sql += ",";
        }
        sql += SQL_PARAM;
    }

    sql += " from " + table_name;

    if (sql_where != "") {
        // TODO: parameterise
        sql += " where " + sql_where;
    }

    // compile SQL query
    SQLite::Statement query(db, sql);

    // now bind values (have to do it at the end, after we've formed the query)
    int bind_count = 1;
    for (std::vector<std::string>::size_type i = 0; i != cols.size(); i++) {
        query.bind(bind_count, cols[i]);
    }

    // and finally execute the command
    while (query.executeStep()) {
        // clear temp. record holder
        cur_record.clear();

        for (int i = 0; i != cols.size(); i++) {
            // columns *do* start at 0, at least
            cur_record.push_back(DBObject("Example"));
            //cur_record.push_back(DBObject(query.getColumn(i)));
        }

        // add record to records list
        records.push_back(cur_record);
    }

    return records;
}
