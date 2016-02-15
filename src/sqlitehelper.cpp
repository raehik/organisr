#include "sqlitehelper.h"
#include "datarecord.h"

#include <stdio.h>
#include "log.h"

const std::string SQLiteHelper::SQL_PARAM = "?";

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
    log_msg("deconstructor called (doing nothing)");
}

void SQLiteHelper::log_msg(std::string message) {
    Util::log("SQLiteHelper: " + message);
}

void SQLiteHelper::log_err(std::string message) {
    Util::error("SQLiteHelper: " + message);
}

bool SQLiteHelper::file_exists(std::string filename) {
    char * FILE_READ = (char *)"r";
    if (FILE *file = fopen(filename.c_str(), FILE_READ)) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

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
        std::vector<DataRecord> rows)
{
    std::string cols_str;

    // check for table existence before anything
    if (! table_exists(table_name)) {
        throw SQLite::Exception("no such table: " + table_name);
    }

    // see http://stackoverflow.com/q/452859/2246637
    if (rows.size() >= 1000) {
        throw SQLite::Exception("trying to insert too many rows (1000 or more)");
    }

    // if no rows passed, throw exception
    if (rows.size() == 0) {
        throw SQLite::Exception("no rows to insert passed (empty array)");
    }

    // columns
    std::string sql = "insert into " + table_name + "(";
    for (std::vector<std::string>::size_type i = 0; i != table_cols.size(); i++) {
        if (i != 0) {
            cols_str += ",";
        }
        cols_str += table_cols[i];
    }
    sql += cols_str + ") values";

    // value placeholders (for binding later)
    for (std::vector<DataRecord>::size_type i = 0; i != rows.size(); i++) {
        if (i != 0) {
            sql += ",";
        }
        sql += "(";
        DataRecord cur_row = rows[i];
        for (int j = 0; j != cur_row.size(); j++) {
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
    for (std::vector<DataRecord>::size_type i = 0; i != rows.size(); i++) {
        DataRecord cur_row = rows[i];
        for (int j = 0; j != cur_row.size(); j++) {
            DataObject obj = cur_row.get_object(j);
            if (obj.type() == "string") {
                query.bind(bind_count, obj.get_str());
            } else if (obj.type() == "int") {
                query.bind(bind_count, obj.get_int());
            } else {
                log_err("DataObject of a type we can't handle");
                return 1;
            }

            bind_count++;
        }
    }
    query.exec();
    return 0;
}

std::vector<DataRecord> SQLiteHelper::select_from_where(
        std::string table_name,
        std::vector<std::string> table_cols,
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
    for (std::vector<std::string>::size_type i = 0; i != table_cols.size(); i++) {
        if (i != 0) {
            sql += ",";
        }
        sql += table_cols[i];
    }

    sql += " from " + table_name;

    // sort the where clause
    if (sql_where != "") {
        log_msg("select: where specified: " + sql_where);
        // TODO: parameterise
        sql += " where " + sql_where;
    }

    // compile SQL query
    SQLite::Statement query(db, sql);
    log_msg("select: compiled: " + sql);

    // and finally execute the command
    std::vector<DataRecord> records;
    while (query.executeStep()) {
        DataRecord cur_record;

        for (unsigned int i = 0; i != table_cols.size(); i++) {
            // columns *do* start at 0, at least
            DataObject tmp("tmp");
            if (query.getColumn(i).isInteger()) {
                tmp = DataObject(query.getColumn(i).getInt());
            } else if (query.getColumn(i).isText()) {
                tmp = DataObject(query.getColumn(i).getText());
            }
            cur_record.add(tmp);
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

        // rethrow after noting error
        throw e;
    }
}

int SQLiteHelper::delete_from_where(std::string table_name, int id) {
    // check for table existence before anything
    if (! table_exists(table_name)) {
        throw SQLite::Exception("no such table: " + table_name);
    }
    return exec_sql("delete from " + table_name + " where id=" + Util::to_string(id));
}

int SQLiteHelper::update_id(std::string table_name, std::string where_col, DataObject where_val, int id) {
    std::string sql;
    // check for table existence before anything
    if (! table_exists(table_name)) {
        throw SQLite::Exception("no such table: " + table_name);
    }

    sql = "update " + table_name + " set " + where_col + "=? where id=" + Util::to_string(id);
    SQLite::Statement stmt(db, sql);
    if (where_val.type() == "string") {
        stmt.bind(1, where_val.get_str());
    } else if (where_val.type() == "int") {
        stmt.bind(1, where_val.get_int());
    } else {
        log_err("DataObject of a type we can't handle");
        return 1;
    }
    return stmt.exec();
}
