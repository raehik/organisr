#include "gnewapptdialog.h"

#include <iostream>
#include "widgetprinter.h"
#include "gwarningbox.h"
#include "log.h"

// Qt includes {{{
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QString>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
// }}}

using namespace Util;

GNewApptDialog::GNewApptDialog(QWidget *parent) : QDialog(parent){
    init_window();
}

void GNewApptDialog::init_window() {
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


    // buttons layout
    QPushButton *b_confirm = new QPushButton("Confirm");
    buttons->addWidget(b_confirm, 0, Qt::AlignRight);

    QPushButton *b_cancel = new QPushButton("Cancel");
    buttons->addWidget(b_cancel, 1, Qt::AlignRight);

    // slots & signals
    connect(b_confirm, SIGNAL(clicked(bool)), this, SLOT(verify_fields()));
    connect(b_cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));

    // put layouts together
    layout->addLayout(form);
    layout->addLayout(buttons);

    this->setLayout(layout);
}

void GNewApptDialog::get_details(QString *title_ptr, QString *desc_ptr) {
    // POINTERS BITCH
    *title_ptr = field_title->text();
    *desc_ptr = field_desc->toPlainText();
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
       log("no title");
       GWarningBox("Field '" + field_name + "' is empty");
        return false;
    } else {
        return true;
    }
}
