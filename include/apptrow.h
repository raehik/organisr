#ifndef APPTROW_H
#define APPTROW_H

#include <string>


class ApptRow
{
public:
    ApptRow(int id, std::string title, std::string desc, int date, int time,
            std::string location);

    int get_id();
    std::string get_title();
    std::string get_desc();
    int get_date();
    int get_time();
    std::string get_location();

private:
    int id;
    std::string title;
    std::string desc;
    int date;
    int time;
    std::string location;
};

#endif // APPTROW_H
