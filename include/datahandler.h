#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <vector>
#include "appointment.h"
#include "sqlitehelper.h"


class DataHandler {
public:
    DataHandler();
    void insert_appts(std::vector<Appointment> appts);

private:
    SQLiteHelper db_helper = SQLiteHelper("test.db");

    static std::string table_appts;
    std::vector<std::string> table_appts_cols; // TODO: static or no?
};

#endif // DATAHANDLER_H
