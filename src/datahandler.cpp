#include "datahandler.h"

#include "appointment.h"
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
    table_appts_cols.push_back("description");
    table_appts_cols.push_back("date");
    table_appts_cols.push_back("location");

    table_todos_cols.push_back("text");
    table_todos_cols.push_back("completed");
}

int DataHandler::init_db() {
    std::string sql_appt = "create table appointments(" \
            "id          integer  primary key," \
            "title       text     not null," \
            "description text," \
            "date        integer," \
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

int DataHandler::insert_appt(DataObject title, DataObject desc, DataObject date, DataObject loc) {
    DataRecord appt;
    appt.add(title);
    appt.add(desc);
    appt.add(date);
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

std::vector<TodoRow> DataHandler::get_todos() {
    std::vector<TodoRow> todos;
    std::vector<std::string> todos_cols_with_id;
    todos_cols_with_id = table_todos_cols;
    todos_cols_with_id.insert(todos_cols_with_id.begin(), "id");
    std::vector<DataRecord> todos_raw = db_helper.select_from_where(TABLE_TODOS, todos_cols_with_id, "");
    for (std::vector<DataRecord>::size_type i = 0; i != todos_raw.size(); i++) {
        DataRecord tmp = todos_raw[i];
        todos.push_back(TodoRow(
                            tmp.get_object(1).get_str(),
                            tmp.get_object(0).get_int(),
                            tmp.get_object(2).get_int()
                            ));
    }
    return todos;
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
