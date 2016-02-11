#include "dataobject.h"

DataObject::DataObject(int val) {
    set_value(val);
}

DataObject::DataObject(std::string val) {
    set_value(val);
}

void DataObject::set_value(int val) {
    obj_type = "int";
    v_int = val;
}

void DataObject::set_value(std::string val) {
    obj_type = "string";
    v_str = val;
}

int DataObject::get_int() {
    return v_int;
}

std::string DataObject::get_str() {
    return v_str;
}

std::string DataObject::type() {
    return obj_type;
}
