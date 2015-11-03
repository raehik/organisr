#include "dbhelper.h"

DBHelper::DBHelper(std::string db_file) {
    set_db_file(db_file);
}

void DBHelper::set_db_file(std::string db_file) {
    this->db_file = db_file;
}
