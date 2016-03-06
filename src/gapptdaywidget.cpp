#include "gapptdaywidget.h"
#include "gnewapptdialog.h"
#include <QLabel>
#include <QDate>
#include <QPushButton>
#include "log.h"

using namespace Util;

const int GApptDayWidget::W_CAL = 280;
const int GApptDayWidget::H_CAL = 185;
const int GApptDayWidget::W_APPTS = 300;

GApptDayWidget::GApptDayWidget(DataHandler *db, QWidget *parent) : QWidget(parent) {
    this->db = db;
    init_window();
}

void GApptDayWidget::init_window() {
    cal = new QCalendarWidget;
    cal->setMaximumSize(W_CAL, H_CAL);
    connect(cal, &QCalendarWidget::selectionChanged, this, &GApptDayWidget::refresh);

    grid = new QGridLayout;
    grid->setColumnStretch(1, 1);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(cal, 0, Qt::AlignTop);
    layout->addLayout(grid);
    this->setLayout(layout);

    refresh();
}

int GApptDayWidget::refresh() {
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
    log("Selected day: " + to_string(julian_day));

    std::vector<RecAppt> appts = db->get_appts_where(to_string(julian_day), "date", "exact");
    log("No. of appts today: " + to_string(appts.size()));

    int grid_y = 0;
    int grid_x = 0;
    if (appts.size() > 0) {
        for (std::vector<RecAppt>::size_type i = 0; i != appts.size(); i++) {
            RecAppt a = appts[i];

            // LABEL: appt. time
            QLabel *tmp_1 = new QLabel("<b>" + QTime(0, 0, 0).addSecs(a.time).toString("HH:mm") + "</b>");
            cur_appts.push_back(tmp_1);
            grid->addWidget(tmp_1, grid_y, grid_x, 1, 1, Qt::AlignTop);

            // LABEL: appt. title
            QLabel *tmp_2 = new QLabel(QString::fromStdString("<b>" + a.title + "</b>"));
            tmp_2->setWordWrap(true);
            tmp_2->setMinimumWidth(W_APPTS);
            cur_appts.push_back(tmp_2);
            grid->addWidget(tmp_2, grid_y, grid_x+1, 1, 1, Qt::AlignTop);

            // LABEL: appt. desc
            QLabel *tmp_3;
            if (a.location != "") {
                tmp_3 = new QLabel(QString::fromStdString("<i>At: " + a.location + "</i><br>" + a.desc));
            } else {
                tmp_3 = new QLabel(QString::fromStdString(a.desc));
            }
            tmp_3->setWordWrap(true);
            grid->addWidget(tmp_3, grid_y+1, grid_x+1, 1, 1, Qt::AlignTop);

            // BUTTON: edit appt.
            QPushButton *b_edit = new QPushButton("E");
            b_edit->setFixedWidth(20);
            grid->addWidget(b_edit, grid_y+1, grid_x, 1, 1, Qt::AlignTop);
            connect(b_edit, &QPushButton::clicked, this, [this, a](){ edit_appt(a.id); });

            // stretch the *long row* (= this row + 1)
            grid->setRowStretch(grid_y+1, 1);

            // update grid positions for next
            // note that we skip a row because we use grid_y and grid_y + 1
            grid_y += 2;
        }
    } else {
        QLabel *tmp_w = new QLabel("No appointments for today!");
        tmp_w->setWordWrap(true);
        tmp_w->setMinimumWidth(W_APPTS);
        grid->addWidget(tmp_w, grid_y, grid_x, 1, 1, Qt::AlignTop);
    }

    return 0;
}

void GApptDayWidget::edit_appt(int id) {
    log("Edit " + to_string(id));
    GNewApptDialog *editor = new GNewApptDialog(this);
    if (editor->exec() == QDialog::Accepted) {
        QString d_title;
        QDate d_date;
        QString d_desc;
        QTime d_time;
        QString d_loc;

        editor->get_details(&d_title, &d_desc, &d_date, &d_time, &d_loc);
        log("updating appt " + d_title.toStdString());
        db->update_appt(
                    id,
                    d_title.toUtf8().toStdString(),
                    d_date.toJulianDay(),
                    d_desc.toUtf8().toStdString(),
                    QTime(0, 0, 0).secsTo(d_time),
                    d_loc.toUtf8().toStdString()
                   );
        refresh();
    }
}
