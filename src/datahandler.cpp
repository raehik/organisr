#include "datahandler.h"

#include "sqlitehelper.h"
#include "log.h"

using namespace Util;

std::string DataHandler::TABLE_APPTS = "appointments";
std::string DataHandler::TABLE_TODOS = "todos";
int DataHandler::TODO_FIN = 1;
int DataHandler::TODO_UNFIN = 0;

DataHandler::DataHandler(std::string db_file) : db_helper(db_file) {
    this->db_file = db_file;

    // check if we need to initialise database
    // TODO: not a good check honestly
    if (! db_helper.table_exists(TABLE_APPTS)) {
        init_db();
    }

    // define column names
    table_appts_cols.push_back("title");
    table_appts_cols.push_back("date");
    table_appts_cols.push_back("description");
    table_appts_cols.push_back("time");
    table_appts_cols.push_back("location");

    table_todos_cols.push_back("text");
    table_todos_cols.push_back("completed");
}

int DataHandler::init_db() {
    std::string sql_appt = "create table appointments(" \
            "id          integer  primary key," \
            "title       text     not null," \
            "date        integer  not null," \
            "description text," \
            "time        integer," \
            "location    text" \
            ");";
    db_helper.exec_sql(sql_appt);

    std::string sql_todo = "create table todos(" \
            "id          integer  primary key," \
            "text        text     not null," \
            "completed   integer" \
            ");";
    db_helper.exec_sql(sql_todo);

    return 0;
}

int DataHandler::insert_appt(DataObject title, DataObject desc, DataObject date, DataObject time, DataObject loc) {
    DataRecord appt;
    appt.add(title);
    appt.add(date);
    appt.add(desc);
    appt.add(time);
    appt.add(loc);
    std::vector<DataRecord> appt_vector;
    appt_vector.push_back(appt);
    db_helper.insert_rows(TABLE_APPTS, table_appts_cols, appt_vector);

    return 0;
}

int DataHandler::insert_todo(std::string text) {
    DataRecord todo;
    todo.add(DataObject(text));
    todo.add(DataObject(TODO_UNFIN));
    std::vector<DataRecord> todo_vector;
    todo_vector.push_back(todo);
    db_helper.insert_rows(TABLE_TODOS, table_todos_cols, todo_vector);

    return 0;
}

std::vector<RecTodo> DataHandler::get_todos() {
    std::vector<RecTodo> todos;
    std::vector<std::string> todos_cols_with_id;
    todos_cols_with_id = table_todos_cols;
    todos_cols_with_id.insert(todos_cols_with_id.begin(), "id");
    std::vector<DataRecord> todos_raw = db_helper.select_from_where(TABLE_TODOS, todos_cols_with_id);
    for (std::vector<DataRecord>::size_type i = 0; i != todos_raw.size(); i++) {
        DataRecord rec_tmp = todos_raw[i];
        RecTodo todo_tmp;
        todo_tmp.id = rec_tmp.get_object(0).get_int();
        todo_tmp.text = rec_tmp.get_object(1).get_str();
        todo_tmp.done = rec_tmp.get_object(2).get_int();
        todos.push_back(todo_tmp);
    }
    return todos;
}

std::vector<RecAppt> DataHandler::get_appts_where(std::string search_str, std::string field, std::string search_type) {
    std::string pre_op;
    std::string post_op;
    std::string query;

    std::vector<std::string> appts_cols_with_id;
    appts_cols_with_id = table_appts_cols;
    appts_cols_with_id.insert(appts_cols_with_id.begin(), "id");

    if (search_type == "anywhere") {
        log("get_appts_where: match anywhere");
        pre_op = "%";
        post_op = "%";
    } else if (search_type == "start") {
        log("get_appts_where: match at start");
        pre_op = "";
        post_op = "%";
    } else if (search_type == "exact") {
        log("get_appts_where: match exact");
        pre_op = "";
        post_op = "";
    } else {
        error("get_appts_where: unknown search type '" + search_type + "'");
    }

    std::string search = pre_op + search_str + post_op;

    if (field == "all") {
        query = "title like '" + search + "' or \
date like '" + search + "' or \
description like '" + search + "%' or \
time like '" + search + "' or \
location like '" + search + "'";
    } else {
        // assume that they gave a valid field (cba to check)
        // TODO
        query = field + " like '" + search + "'";
    }

    std::vector<DataRecord> match_recs = db_helper.select_from_where(TABLE_APPTS, appts_cols_with_id, query);
    std::vector<RecAppt> match_appts = appt_recs_to_appts(match_recs);
    return match_appts;
}

int DataHandler::delete_todo(int id) {
    return db_helper.delete_from_where(TABLE_TODOS, id);
}

int DataHandler::update_todo(int id, std::string text) {
    return db_helper.update_id(TABLE_TODOS, "text", DataObject(text), id);
}

int DataHandler::complete_todo(int id) {
    return db_helper.update_id(TABLE_TODOS, "completed", DataObject(TODO_FIN), id);
}

int DataHandler::uncomplete_todo(int id) {
    return db_helper.update_id(TABLE_TODOS, "completed", DataObject(TODO_UNFIN), id);
}

int DataHandler::delete_appt(int id) {
    return db_helper.delete_from_where(TABLE_APPTS, id);
}

int DataHandler::update_appt(int id, std::string title, int date, std::string desc, int time, std::string loc) {
    // TODO: this is especially unneat and slow...
    db_helper.update_id(TABLE_APPTS, "title", DataObject(title), id);
    db_helper.update_id(TABLE_APPTS, "date", DataObject(date), id);
    db_helper.update_id(TABLE_APPTS, "description", DataObject(desc), id);
    db_helper.update_id(TABLE_APPTS, "time", DataObject(time), id);
    return db_helper.update_id(TABLE_APPTS, "location", DataObject(loc), id);
}

std::vector<RecAppt> DataHandler::search_appts(
        std::string f_title,
        std::string f_desc,
        int f_date_before,
        int f_date_after,
        std::string f_loc)
{
    std::vector<std::string> appts_cols_with_id;
    appts_cols_with_id = table_appts_cols;
    appts_cols_with_id.insert(appts_cols_with_id.begin(), "id");

    std::string pre_op = "%";
    std::string post_op = "%";
    std::string sql = "title like '" + pre_op + f_title + post_op + "' and \
description like '" + pre_op + f_desc + post_op + "' and \
date <= " + to_string(f_date_before) + " and \
date >= " + to_string(f_date_after) + " and \
location like '" + pre_op + f_loc + post_op + "'";

    std::vector<DataRecord> match_recs = db_helper.select_from_where(TABLE_APPTS, appts_cols_with_id, sql);
    std::vector<RecAppt> match_appts = appt_recs_to_appts(match_recs);
    return match_appts;
}

std::vector<RecAppt> DataHandler::appt_recs_to_appts(std::vector<DataRecord> records) {
    std::vector<RecAppt> appts;
    for (std::vector<DataRecord>::size_type i = 0; i != records.size(); i++) {
        DataRecord rec = records[i];
        RecAppt appt_tmp;
        appt_tmp.id = rec.get_object(0).get_int();
        appt_tmp.title = rec.get_object(1).get_str();
        appt_tmp.date = rec.get_object(2).get_int();
        appt_tmp.desc = rec.get_object(3).get_str();
        appt_tmp.time = rec.get_object(4).get_int();
        appt_tmp.location = rec.get_object(5).get_str();
        appts.push_back(appt_tmp);
    }
    return appts;
}
