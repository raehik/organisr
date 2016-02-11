#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <string>

class DataObject
{
public:
    DataObject(int val);
    DataObject(std::string val);

    int get_int();
    std::string get_str();

    void set_value(int var);
    void set_value(std::string var);

    std::string type();

private:
    int v_int;
    std::string v_str;
    std::string obj_type;
};

#endif // DATAOBJECT_H
