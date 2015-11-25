#include "newapptdialog.h"
#include <iostream>
#include "log.h"

NewApptDialog::NewApptDialog(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Dialog);
}

void NewApptDialog::accepted() {
    log("Accepted");
}

void NewApptDialog::cancelled() {
    log("Cancelled");
}
