#include "gnewtododialog.h"

#include "rectodo.h"

#include "gwarningbox.h"
#include "log.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QFormLayout>

using namespace Util;

GNewTodoDialog::GNewTodoDialog(QWidget *parent, RecTodo placeholder) : QDialog(parent){
    log("add/edit to-do dialog");
    init_window(placeholder);
}

void GNewTodoDialog::init_window(RecTodo placeholder) {
    // window size
    this->setFixedWidth(250);

    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *form = new QFormLayout;
    QHBoxLayout *buttons = new QHBoxLayout;

    // form layout
    label_text = new QLabel("To-do");
    field_text = new QLineEdit;
    if (placeholder.id != 0) {
        // received a placeholder: we're EDITING, not adding
        field_text->setText(QString::fromStdString(placeholder.text));
        this->setWindowTitle("Edit to-do");
    } else {
        this->setWindowTitle("Add to-do");
    }
    form->addRow(label_text, field_text);

    // buttons layout
    QPushButton *b_confirm = new QPushButton("Confirm");
    buttons->addWidget(b_confirm, 0, Qt::AlignRight);

    QPushButton *b_cancel = new QPushButton("Cancel");
    buttons->addWidget(b_cancel, 1, Qt::AlignRight);

    // slots & signals
    connect(b_confirm, &QPushButton::clicked, this, &GNewTodoDialog::verify_fields);
    connect(b_cancel, &QPushButton::clicked, this, &GNewTodoDialog::reject);

    // put layouts together
    layout->addLayout(form);
    layout->addLayout(buttons);

    this->setLayout(layout);
}

void GNewTodoDialog::get_details(QString *text_ptr) {
    // POINTERS BITCH
    *text_ptr = field_text->text();
}

int GNewTodoDialog::verify_fields() {
   QString text = field_text->text();

   // check that certain fields aren't empty
   if ( field_not_empty(text, label_text->text()) ) {
       accept();
   }
   return 0;
}

bool GNewTodoDialog::field_not_empty(QString field_text, QString field_name) {
    if (field_text == "") {
       GWarningBox("Field '" + field_name + "' is empty");
        return false;
    } else {
        return true;
    }
}
