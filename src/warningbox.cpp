#include "warningbox.h"

WarningBox::WarningBox(QString text, QWidget *parent) : QMessageBox(parent) {
    QString def_title = "Error";
    this->setIcon(QMessageBox::Warning);
    this->setWindowTitle(def_title);
    this->setText(text);

    this->exec();
}
