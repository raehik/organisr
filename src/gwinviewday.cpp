#include "gwinviewday.h"
#include "log.h"

using namespace Util;

GWinViewDay::GWinViewDay(DataHandler *db, QWidget *parent) : QDialog(parent) {
    this->db = db;
    init_window();
}

void GWinViewDay::init_window() {
    std::vector<RecAppt> appts = db->get_appts_where("doge");

    log(appts[0].title);
    log("Wow: " + to_string(appts.size()));
}
