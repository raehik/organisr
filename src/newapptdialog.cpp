#include "newapptdialog.h"
#include <iostream>

NewApptDialog::NewApptDialog(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Dialog);
}

void NewApptDialog::accepted() {
    std::cout << "Accepted" << std::endl;
}

void NewApptDialog::cancelled() {
    std::cout << "Cancelled" << std::endl;
}
