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

std::string DBObject::type() {
    return obj_type;
}

int DBObject::get_int() {
    return int_val;
}

std::string DBObject::get_str() {
    return str_val;
}
