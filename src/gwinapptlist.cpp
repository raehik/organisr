#include "gwinapptlist.h"

#include <QScrollArea>
#include <QBoxLayout>
#include <QDate>
#include <QLabel>

#include "log.h"

using namespace Util;

GWinApptList::GWinApptList(std::vector<RecAppt> appts, QWidget *parent) : QDialog(parent) {
    this->appts = appts;
    init_window();
}


void GWinApptList::init_window() {
    this->setWindowTitle("Search results");
    this->resize(250, 400);

    QVBoxLayout *appt_details = new QVBoxLayout;

    // create a widget for each appointment
    for (std::vector<RecAppt>::size_type i = 0; i != this->appts.size(); i++) {
        // form labels etc.
        RecAppt appt = appts[i];
        QDate appt_date = QDate::fromJulianDay(appt.date);
        QTime appt_time = QTime(0, 0, 0).addSecs(appt.time);

        QLabel *l_date = new QLabel(
                    "<h3>"
                    + appt_date.toString("ddd' 'd' 'MMM' 'yyyy")
                    + "</h3>"
        );
        QLabel *l_time_loc = new QLabel(
                    appt_time.toString("hh:mm")
                    + " at "
                    + QString::fromStdString(appt.location)
        );
        l_time_loc->setStyleSheet("color: grey");
        QLabel *l_title = new QLabel(
                    "&nbsp;&nbsp;"
                    + QString::fromStdString(appt.title)
        );
        l_title->setWordWrap(true);
        l_title->setTextFormat(Qt::RichText);
        QLabel *l_desc = new QLabel(
                    "&nbsp;&nbsp;&nbsp;&nbsp;"
                    + QString::fromStdString(appt.desc)
        );
        l_desc->setWordWrap(true);
        l_desc->setTextFormat(Qt::RichText);

        // add to appointment list
        appt_details->addWidget(l_date);
        if (! appt.location.empty()) { appt_details->addWidget(l_time_loc); }
        appt_details->addWidget(l_title);
        if (! appt.desc.empty()) { appt_details->addWidget(l_desc); }
    }

    QWidget *scroll_widget = new QWidget;
    scroll_widget->setLayout(appt_details);

    // set up scroller
    QScrollArea *scroller = new QScrollArea;
    scroller->setWidget(scroll_widget);
    scroller->setWidgetResizable(true);

    QVBoxLayout *tmp = new QVBoxLayout;
    tmp->addWidget(scroller);

    this->setLayout(tmp);
}
