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
    int insert_appts(std::vector<Appointment> appts);
    int insert_appt(DBObject title, DBObject desc);

private:
    SQLiteHelper db_helper;

    static std::string db_file;
    static std::string table_appts;
    std::vector<std::string> table_appts_cols; // TODO: static or no?
};

#endif // DATAHANDLER_H
