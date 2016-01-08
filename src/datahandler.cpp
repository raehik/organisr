#include "datahandler.h"

#include "appointment.h"
#include "sqlitehelper.h"

std::string DataHandler::table_appts = "appointments";
std::string DataHandler::table_todos = "todos";

DataHandler::DataHandler(std::string db_file) : db_helper(db_file) {
    this->db_file = db_file;

    // check if we need to initialise database
    // TODO: not a good check honestly
    if (! db_helper.table_exists(table_appts)) {
        init_db();
    }

    // define column names
    table_appts_cols.push_back("title");
    table_appts_cols.push_back("description");

    table_todos_cols.push_back("text");
}

int DataHandler::init_db() {
    std::string sql_appt = "create table appointments(" \
            "id          integer  primary key," \
            "title       text     not null," \
            "description text);";
    db_helper.exec_sql(sql_appt);

    std::string sql_todo = "create table todos(" \
            "id          integer  primary key," \
            "text        text     not null);";
    db_helper.exec_sql(sql_todo);

    return 0;
}

int DataHandler::insert_appts(std::vector<Appointment> objects) {
    /*
     * The information a database needs to insert a row into a table is:
     *   * table name
     *   * ordered column names
     *   * ordered insert values
     *   * knowledge of insert value types (TODO: maybe?)
     * We don't provide the ID and instead assume that the DB helper sorts that
     * for us in some way (it can be omitted if configured correctly).
     *
     * TODO: you're limited to ~1000 inserts for one statement, test it
     */
    std::vector< std::vector<DBObject> > rows;
    std::vector<DBObject> row;
    for (std::vector<Appointment>::size_type i = 0; i != objects.size(); i++) {
        // clear insert vector
        row.clear();

        // append info for one insert
        row.push_back(DBObject(objects[i].title));
        row.push_back(DBObject(objects[i].description));

        // add to vector vector
        rows.push_back(row);
    }
    int rc = db_helper.insert_rows(table_appts, table_appts_cols, rows);
    return rc;
}

int DataHandler::insert_appt(DBObject title, DBObject desc) {
    std::vector<DBObject> appt;
    appt.push_back(title);
    appt.push_back(desc);
    std::vector< std::vector<DBObject> > appt_vector;
    appt_vector.push_back(appt);
    db_helper.insert_rows(table_appts, table_appts_cols, appt_vector);

    return 0;
}

int DataHandler::insert_todo(std::string text) {
    std::vector<DBObject> todo;
    todo.push_back(DBObject(text));
    std::vector< std::vector<DBObject> > todo_vector;
    db_helper.insert_rows(table_todos, table_todos_cols, todo_vector);

    return 0;
}
