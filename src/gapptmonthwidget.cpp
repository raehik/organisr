#include "gapptmonthwidget.h"
#include "gwidgetprinter.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "log.h"

using namespace Util;

const int GApptMonthWidget::WIN_X = 800;
const int GApptMonthWidget::WIN_Y = 500;
const int GApptMonthWidget::CAL_WIDTH = 7;

GApptMonthWidget::GApptMonthWidget(QDate date, DataHandler *db, QWidget *parent) : QDialog(parent) {
    this->db = db;
    this->date = date;
    init_window();
}

void GApptMonthWidget::init_window() {
    // resize
    resize(WIN_X, WIN_Y);

    day_grid = new QGridLayout;
    day_grid->setHorizontalSpacing(0);
    day_grid->setVerticalSpacing(0);
    //day_grid->setColumnStretch(1, 1);

    QPushButton *b_print = new QPushButton("Print");
    connect(b_print, &QPushButton::clicked, this, &GApptMonthWidget::make_printout);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(day_grid);
    layout->addWidget(b_print, 0, Qt::AlignRight);
    this->setLayout(layout);

    refresh();
}

int GApptMonthWidget::refresh() {
    // clear grid
    // This took me **1 hour** to find. jfc
    // thanks chrisnew from:
    // http://www.qtcentre.org/threads/14701-Trying-to-refresh-a-QGridLayout
    while (day_grid->count() > 0) {
        QWidget* widget = day_grid->itemAt(0)->widget();
        day_grid->removeWidget(widget);
        delete widget;
    }

    // get appointments for each day & add to respective grid cell
    int d_year, d_month, d_day;
    int grid_x, grid_y = 0;
    date.getDate(&d_year, &d_month, &d_day);
    for (int day_num = 1; day_num < date.daysInMonth() + 1; day_num++) {
        int check_date = QDate(d_year, d_month, day_num).toJulianDay();
        std::vector<RecAppt> appts = db->get_appts_where(to_string(check_date), "date", "exact");

        QVBoxLayout *day_layout = new QVBoxLayout;

        // for each appointment in each day
        for (std::vector<RecAppt>::size_type i = 0; i != appts.size(); i++) {
            RecAppt a = appts[i];
            QLabel *cur_appt = new QLabel(QString::fromStdString(a.title));
            cur_appt->setWordWrap(true);
            cur_appt->setStyleSheet("background-color: grey; border-style: solid; border-width: 1px");
            cur_appt->resize(300, 300);

            day_layout->addWidget(cur_appt);
        }

        // alternative if there were no appointments
        if (appts.size() == 0) {
            QLabel *empty_day = new QLabel(QString::fromStdString(to_string(day_num)));;
            empty_day ->setStyleSheet("background-color: white; border-style: solid; border-width: 1px");
            empty_day ->resize(300, 300);
            day_layout->addWidget(empty_day);
        }

        day_grid->addLayout(day_layout, grid_y, grid_x);


        // increment grid positions
        grid_x++;
        if (grid_x > CAL_WIDTH - 1) {
            grid_x = 0;
            grid_y++;
        }
    }
    return 0;
}

void GApptMonthWidget::make_printout() {
    log("Making printout");
    //QWidget *tmp_widget = new QWidget;
    //tmp_widget->setLayout(day_grid);
    GWidgetPrinter printer(this, "Print appointments", true);
    printer.dialogAndPrint();
}
