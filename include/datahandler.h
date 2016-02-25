#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <vector>
#include "todorow.h"
#include "apptrow.h"
#include "sqlitehelper.h"


class DataHandler
{
public:
    DataHandler(std::string db_file);
    int init_db();
    int insert_appt(DataObject title, DataObject desc, DataObject date, DataObject time, DataObject loc);
    int insert_todo(std::string text);
    int complete_todo(int id);
    int uncomplete_todo(int id);
    int update_todo(int id, std::string text);
    int delete_todo(int id);
    std::vector<TodoRow> get_todos();
    std::vector<ApptRow> get_appts_where(std::string search_str);

    static int TODO_FIN;
    static int TODO_UNFIN;

private:
    SQLiteHelper db_helper;

    std::string db_file;

    static std::string TABLE_APPTS;
    static std::string TABLE_TODOS;

    std::vector<std::string> table_appts_cols; // TODO: static or no?
    std::vector<std::string> table_todos_cols;
};

#endif // DATAHANDLER_H
