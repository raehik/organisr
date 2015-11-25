#include "warningbox.h"

WarningBox::WarningBox(QString title, QString text, QWidget *parent) : QMessageBox(parent) {
    this->setIcon(QMessageBox::Warning);
    this->setWindowTitle(title);
    this->setText(text);

    this->exec();
}
