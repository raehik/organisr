#include "guimainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include "newapptdialog.h"
#include "log.h"

GuiMainWindow::GuiMainWindow() {
    init_window();
    db = DataHandler();

    // do logic stuff
    //std::vector<Appointment> appts;
    //appts.push_back(Appointment("test title 1", "test desc 1"));
    //db.insert_appts(appts);
}

/**
 * Initialise the main window.
 */
void GuiMainWindow::init_window() {
    // uncomment for floating main window
    this->setWindowFlags(Qt::Dialog);

    QHBoxLayout *layout = new QHBoxLayout;

    QPushButton *b_new_appt = new QPushButton("Add new appointment");
    QPushButton *b_new_todo = new QPushButton("Add new to-do");

    layout->addWidget(b_new_appt, 0);
    layout->addWidget(b_new_todo, 1, Qt::AlignRight);

    connect(b_new_appt, SIGNAL(clicked()), this, SLOT(open_new_appt_dialog()));

    QWidget *main_widget = new QWidget;
    main_widget->setLayout(layout);
    setCentralWidget(main_widget);
}

void GuiMainWindow::open_new_appt_dialog() {
    log("opening new appt. dialog");
    NewApptDialog *w_appt_dialog = new NewApptDialog(this);
    if (w_appt_dialog->exec() == QDialog::Accepted) {
        QString appt_title;
        QString appt_desc;
        w_appt_dialog->get_details(&appt_title, &appt_desc);
        log(appt_title.toUtf8().constData());
        log(appt_desc.toUtf8().constData());
    }
    //connect(w_appt_dialog, SIGNAL(accepted()), this, SLOT(add_new_appt(w_appt_dialog)));
    //connect(w_appt_dialog, SIGNAL(rejected()), this, SLOT(rejected? or sth()));
}
