#include "gnewapptdialog.h"

#include "recappt.h"

#include "gwarningbox.h"
#include "log.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>

using namespace Util;

GNewApptDialog::GNewApptDialog(QWidget *parent, RecAppt placeholder) : QDialog(parent){
    init_window(placeholder);
}

void GNewApptDialog::init_window(RecAppt placeholder) {
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *form = new QFormLayout;
    QHBoxLayout *buttons = new QHBoxLayout;

    // form layout
    label_title = new QLabel("Title");
    field_title = new QLineEdit;
    form->addRow(label_title, field_title);

    label_desc = new QLabel("Description");
    field_desc = new QTextEdit;
    form->addRow(label_desc, field_desc);

    label_date = new QLabel("Date");
    field_date = new QCalendarWidget;
    form->addRow(label_date, field_date);

    label_time = new QLabel("Time");
    field_time = new QTimeEdit;
    form->addRow(label_time, field_time);

    label_loc = new QLabel("Location");
    field_loc = new QLineEdit;
    form->addRow(label_loc, field_loc);

    // if given non-empty placeholder, change some properties
    if (placeholder.id != 0) {
        this->setWindowTitle("Edit appointment");
        field_title->setText(QString::fromStdString(placeholder.title));
        field_desc->setText(QString::fromStdString(placeholder.desc));
        field_date->setSelectedDate(QDate::fromJulianDay(placeholder.date));
        field_time->setTime(QTime::fromMSecsSinceStartOfDay(placeholder.time));
        field_loc->setText(QString::fromStdString(placeholder.location));
    } else {
        this->setWindowTitle("Add appointment");
    }


    // buttons layout
    QPushButton *b_confirm = new QPushButton("Confirm");
    buttons->addWidget(b_confirm, 0, Qt::AlignRight);

    QPushButton *b_cancel = new QPushButton("Cancel");
    buttons->addWidget(b_cancel, 1, Qt::AlignRight);

    // slots & signals
    connect(b_confirm, &QPushButton::clicked, this, &GNewApptDialog::verify_fields);
    connect(b_cancel, &QPushButton::clicked, this, &GNewApptDialog::reject);

    // put layouts together
    layout->addLayout(form);
    layout->addLayout(buttons);

    this->setLayout(layout);
}

void GNewApptDialog::get_details(QString *title_ptr, QString *desc_ptr, QDate *date_ptr, QTime *time_ptr, QString *loc_ptr) {
    // POINTERS BITCH
    *title_ptr = field_title->text();
    *desc_ptr = field_desc->toPlainText();
    *date_ptr = field_date->selectedDate();
    *time_ptr = field_time->time();
    *loc_ptr = field_loc->text();
}

int GNewApptDialog::verify_fields() {
   QString title = field_title->text();

   // check that certain fields aren't empty
   if ( field_not_empty(title, label_title->text()) ) {
       accept();
   }
   return 0;
}

bool GNewApptDialog::field_not_empty(QString field_text, QString field_name) {
    if (field_text == "") {
       GWarningBox("Field '" + field_name + "' is empty");
        return false;
    } else {
        return true;
    }
}
