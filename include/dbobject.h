#ifndef DBOBJECT_H
#define DBOBJECT_H

#include <string>

class DBObject
{
public:
    DBObject(int);
    DBObject(std::string);

    std::string type();

    int get_int();
    std::string get_str();

    void get_value(int*);
    void get_value(std::string*);

private:
    int int_val;
    std::string str_val;
    std::string obj_type;
};

#endif // DBOBJECT_H
