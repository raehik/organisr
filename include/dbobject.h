#ifndef DBOBJECT_H
#define DBOBJECT_H

#include <string>

class DBObject
{
public:
    DBObject(int value);
    DBObject(std::string value);
    template <typename T> T get_value();
    std::string get_str();

private:
    int int_val;
    std::string str_val;
    std::string obj_type;
};

#endif // DBOBJECT_H
