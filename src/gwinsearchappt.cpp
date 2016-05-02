#include "gwinsearchappt.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include "gwarningbox.h"
#include "gwinapptlist.h"
#include "log.h"

using namespace Util;

GWinSearchAppt::GWinSearchAppt(DataHandler *db, QWidget *parent) : QDialog(parent) {
    this->db = db;
    init_window();
}

void GWinSearchAppt::init_window() {
    this->setWindowTitle("Search appointments");

    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *form = new QFormLayout;
    QHBoxLayout *buttons = new QHBoxLayout;

    // form elements
    l_title = new QLabel("Title/description");
    f_title = new QLineEdit;
    form->addRow(l_title, f_title);

    l_date_after = new QLabel("After date");
    f_date_after = new QCalendarWidget;
    form->addRow(l_date_after, f_date_after);

    l_date_before = new QLabel("Before date");
    f_date_before = new QCalendarWidget;
    form->addRow(l_date_before, f_date_before);

    l_loc = new QLabel("Location");
    f_loc = new QLineEdit;
    form->addRow(l_loc, f_loc);

    // confirm/cancel buttons
    QPushButton *b_confirm = new QPushButton("Confirm");
    buttons->addWidget(b_confirm, 0, Qt::AlignRight);

    QPushButton *b_cancel = new QPushButton("Cancel");
    buttons->addWidget(b_cancel, 1, Qt::AlignRight);

    // slots & signals
    connect(b_confirm, &QPushButton::clicked, this, &GWinSearchAppt::run_search);
    connect(b_cancel, &QPushButton::clicked, this, &GWinSearchAppt::reject);

    // put the layouts together
    layout->addWidget(new QLabel("Find appointments matching..."));
    layout->addLayout(form);
    layout->addLayout(buttons);

    this->setLayout(layout);
}

void GWinSearchAppt::run_search() {
    log("GWinSearchAppt: searching...");
    QString s_title = f_title->text();
    QDate s_date_before = f_date_before->selectedDate();
    QDate s_date_after = f_date_after->selectedDate();
    QString s_loc = f_loc->text();
    std::vector<RecAppt> matches = db->search_appts(
            s_title.toStdString(),
            s_title.toStdString(),
            s_date_before.toJulianDay(),
            s_date_after.toJulianDay(),
            s_loc.toStdString()
    );

    if (matches.size() == 0) {
        GWarningBox("No appointments found for given range and descriptions.");
    } else {
        GWinApptList(matches, this);
    }

    // TODO: check that at least one field is filled
}
