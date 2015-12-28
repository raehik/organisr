#include "warningbox.h"
#include "log.h"

WarningBox::WarningBox(QString text, QWidget *parent) : QMessageBox(parent) {
    QString def_title = "Error";
    this->setIcon(QMessageBox::Warning);
    this->setWindowTitle(def_title);
    this->setText(text);

    this->exec();
}

/**
 * Show when the WarningBox is deleted (for debugging purposes).
 */
WarningBox::~WarningBox() {
    Util::log("warning box deleting");
}
