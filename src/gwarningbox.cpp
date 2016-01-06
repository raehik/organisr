#include "gwarningbox.h"
#include "log.h"

GWarningBox::GWarningBox(QString text, QWidget *parent) : QMessageBox(parent) {
    QString def_title = "Error";
    this->setIcon(QMessageBox::Warning);
    this->setWindowTitle(def_title);
    this->setText(text);

    this->exec();
}

/**
 * Show when the WarningBox is deleted (for debugging purposes).
 */
GWarningBox::~GWarningBox() {
    Util::log("warning box deleting");
}
