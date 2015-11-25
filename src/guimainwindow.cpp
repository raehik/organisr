#include "guimainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include "newapptdialog.h"
#include "log.h"

GuiMainWindow::GuiMainWindow() {
    init_window();
}

/**
 * Initialise the main window.
 */
void GuiMainWindow::init_window() {
    // uncomment for floating main window
    this->setWindowFlags(Qt::Dialog);

    QHBoxLayout *layout = new QHBoxLayout();

    QPushButton *b_new_appt = new QPushButton("Add new appointment", this);
    QPushButton *b_new_todo = new QPushButton("Add new to-do", this);

    layout->addWidget(b_new_appt, 0);
    layout->addWidget(b_new_todo, 1, Qt::AlignRight);

    connect(b_new_appt, SIGNAL(clicked()), this, SLOT(open_new_appt_dialog()));

    QWidget *main_widget = new QWidget();
    main_widget->setLayout(layout);
    setCentralWidget(main_widget);
}

void GuiMainWindow::open_new_appt_dialog() {
    log("opening new appt. dialog");
    NewApptDialog *w_appt_dialog = new NewApptDialog();
}
