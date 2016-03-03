#include "gwinviewday.h"
#include <QLabel>
#include <QDate>
#include "log.h"

using namespace Util;

GWinViewDay::GWinViewDay(DataHandler *db, QWidget *parent) : QDialog(parent) {
    this->db = db;
    init_window();
}

void GWinViewDay::init_window() {
    cal = new QCalendarWidget;
    connect(cal, &QCalendarWidget::selectionChanged, this, &GWinViewDay::update_appts);

    grid = new QGridLayout;
    layout = new QHBoxLayout;
    layout->addWidget(cal);
    layout->addLayout(grid);
    this->setLayout(layout);

    update_appts();
}

int GWinViewDay::update_appts() {
    // clear grid
    // This took me **1 hour** to find. jfc
    // thanks chrisnew from:
    // http://www.qtcentre.org/threads/14701-Trying-to-refresh-a-QGridLayout
    while (grid->count() > 0) {
        QWidget* widget = grid->itemAt(0)->widget();
        grid->removeWidget(widget);
        delete widget;
    }

    int julian_day = cal->selectedDate().toJulianDay();
    log("Selected day:" + to_string(julian_day));

    std::vector<RecAppt> appts = db->get_appts_where(to_string(julian_day), "date", "exact");
    log("No. of appts today: " + to_string(appts.size()));

    int grid_y = 0;
    int grid_x = 0;
    for (std::vector<RecAppt>::size_type i = 0; i != appts.size(); i++) {
        RecAppt a = appts[i];
        QLabel *tmp_1 = new QLabel("<b>" + QTime(0, 0, 0).addSecs(a.time).toString("HH:mm") + "</b>");
        cur_appts.push_back(tmp_1);
        QLabel *tmp_2 = new QLabel(QString::fromStdString(a.title));
        cur_appts.push_back(tmp_2);

        grid->addWidget(tmp_1, grid_y, grid_x, 1, 1);
        grid->addWidget(tmp_2, grid_y, grid_x+1, 1, 1);

        // update grid positions for next
        grid_x = 0;
        grid_y++;
    }

    return 0;
}
