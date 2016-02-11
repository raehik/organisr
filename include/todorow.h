#ifndef TODOROW_H
#define TODOROW_H

#include <string>


class TodoRow
{
public:
    TodoRow(std::string text, int id, int done);
    std::string get_text();
    int get_id();
    bool get_done();

private:
    std::string text;
    int id;
    bool done;
};

#endif // TODOROW_H
