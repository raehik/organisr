#include "dbobject.h"

DBObject::DBObject(int value) {
    obj_type = "int";
    int_val = value;
}

DBObject::DBObject(std::string value) {
    obj_type = "string";
    str_val = value;
}

template <typename T> T DBObject::get_value() {
    if (obj_type == "int") {
        return int_val;
    } else if (obj_type == "string") {
        return str_val;
    }
}

std::string DBObject::get_str() {
    return str_val;
}
