#include "sqlitehelper.h"

#include <stdio.h>
#include "log.h"

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
    log_msg("opened database " + db_file + " successfully");
}
catch(SQLite::Exception e) {
    log_err("SQLite database open or creation failed (file was " + db_file + " )");

    // just throw e again after catching it lol
    throw e;
}

SQLiteHelper::~SQLiteHelper() {
    log_msg("closing DB");
}

void SQLiteHelper::log_msg(std::string message) {
    Util::log("SQLiteHelper: " + message);
}

void SQLiteHelper::log_err(std::string message) {
    Util::error("SQLiteHelper: " + message);
}

/**
 * Check if a file exists.
 *
 * Currently unused, but I would be using it if I could be (SQLiteCPP forces you
 * to open the DB in the constructor, and it makes the file).
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
 * @brief SQLiteHelper::open_db
 * @return 0
 */
int SQLiteHelper::open_db() {
    // for now, we are forced to open the database in the constructor, so this
    // does nothing
    return 0;
}

/**
 * Execute a set of SQL statements.
 *
 * @return always returns 0
 * @throw SQLite::Exception in case of error
 */
int SQLiteHelper::exec_sql(std::string statement) {
    if (statement.size() == 0) {
        log_msg("exec statement is empty");
        return 0;
    } else {
        log_msg("exec: '" + statement + "'");
        db.exec(statement);
        return 0;
    }
}

std::string SQLiteHelper::get_errmsg() {
    return db.errmsg();
}

int SQLiteHelper::insert_rows(
        std::string table_name,
        std::vector<std::string> table_cols,
        std::vector< std::vector<DBObject> > rows)
{
    std::string cols_str;
    std::vector<DBObject> cur_row;

    // check for table existence before anything
    if (! table_exists(table_name)) {
        throw SQLite::Exception("no such table: " + table_name);
    }

    // see http://stackoverflow.com/q/452859/2246637
    if (rows.size() >= 1000) {
        throw SQLite::Exception("trying to insert too many rows (1000 or more)");
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
                log_err("DBObject of a type we can't handle");
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
    std::string sql;

    // check for table existence before anything
    if (! table_exists(table_name)) {
        throw SQLite::Exception("no such table: " + table_name);
    }

    // start the query
    sql = "select ";

    // select specified columns
    log_msg("select: setting columns");
    for (std::vector<std::string>::size_type i = 0; i != cols.size(); i++) {
        if (i != 0) {
            sql += ",";
        }
        sql += cols[i];
    }

    sql += " from " + table_name;

    if (sql_where != "") {
        log_msg("select: where specified: " + sql_where);
        // TODO: parameterise
        sql += " where " + sql_where;
    }
        log_msg("select: no where specified");

    // compile SQL query
    SQLite::Statement query(db, sql);
    log_msg("select: compiled: " + sql);

    // and finally execute the command
    std::vector<DBObject> cur_record;
    std::vector< std::vector<DBObject> > records;
    while (query.executeStep()) {
        // clear temp. record holder
        cur_record.clear();

        for (int i = 0; i != cols.size(); i++) {
            // columns *do* start at 0, at least
            DBObject tmp("tmp");
            if (query.getColumn(i).isInteger()) {
                tmp = DBObject(query.getColumn(i).getInt());
            } else if (query.getColumn(i).isText()) {
                tmp = DBObject(query.getColumn(i).getText());
            }
            cur_record.push_back(tmp);
        }

        // add record to records list
        records.push_back(cur_record);
    }
    log_msg("select: finished executing command");

    return records;
}

bool SQLiteHelper::table_exists(std::string table) {
    try {
        if (db.tableExists(table)) {
            log_msg("table " + table + " exists");
            return true;
        } else {
            log_msg("table " + table + " does not exist");
            return false;
        }
    } catch(SQLite::Exception e) {
        log_err("exception when checking for existence of table " + table);
        return false;
    }
}
