#include "apptrow.h"
#include "datahandler.h"
#include "log.h"

using namespace Util;

ApptRow::ApptRow(int id, std::string title, std::string desc, int date, int time, std::string location) {
    // set all the fields for a single record
    this->id = id;
    this->title = title;
    this->desc = desc;
    this->date = date;
    this->time = time;
    this->location = location;
}

int ApptRow::get_id() {
    return id;
}

std::string ApptRow::get_title() {
    return title;
}

std::string ApptRow::get_desc() {
    return desc;
}

int ApptRow::get_date() {
    return date;
}

int ApptRow::get_time() {
    return time;
}

std::string ApptRow::get_location() {
    return location;
}
