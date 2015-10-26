#include "datahandler.h"
#include "appointment.h"
#include "sqlitehelper.h"
#include <vector>

DataHandler::DataHandler() {
    SQLiteHelper db_helper = SQLiteHelper("test.db");
}

void DataHandler::insert_appts(std::vector<Appointment> appts) {
    std::cout << appts[0].title;
}
