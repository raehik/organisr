#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <vector>
#include "appointment.h"
#include "sqlitehelper.h"


class DataHandler
{
public:
    DataHandler();
    int init_db();
    int insert_appts(std::vector<Appointment> appts);
    int insert_appt(DBObject title, DBObject desc);
    int insert_todo(std::string text);

private:
    SQLiteHelper db_helper;

    static std::string db_file;
    static std::string table_appts;
    static std::string table_todos;
    std::vector<std::string> table_appts_cols; // TODO: static or no?
    std::vector<std::string> table_todos_cols;
};

#endif // DATAHANDLER_H
