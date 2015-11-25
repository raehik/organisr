#include "newapptdialog.h"
#include <iostream>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include "log.h"

NewApptDialog::NewApptDialog(QWidget *parent) : QWidget(parent){
    init_window();
    this->show();
}

void NewApptDialog::init_window() {
    // set hints (makes windows floating on certain Linux window managers)
    this->setWindowFlags(Qt::Dialog);

    QFormLayout *layout = new QFormLayout;

    QLabel *label_title = new QLabel("Title");
    QLineEdit *field_title = new QLineEdit;
    QLabel *label_desc = new QLabel("Description");
    QTextEdit *field_desc = new QTextEdit;

    layout->addRow(label_title, field_title);
    layout->addRow(label_desc, field_desc);

    this->setLayout(layout);
}

void NewApptDialog::accepted() {
    log("Accepted");
}

void NewApptDialog::cancelled() {
    log("Cancelled");
}
