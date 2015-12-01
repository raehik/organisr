#include "dbobject.h"

DBObject::DBObject(int value) {
    obj_type = "int";
    int_val = value;
}

DBObject::DBObject(std::string value) {
    obj_type = "string";
    str_val = value;
}

void DBObject::get_value(int *var) {
    *var = int_val;
}
void DBObject::get_value(std::string *var) {
    *var = str_val;
}
