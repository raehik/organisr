#include "guimainwindow.h"

#include <vector>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>

#include "newapptdialog.h"
#include "todolistwidget.h"
#include "appointment.h"
#include "log.h"

using namespace Util;

GuiMainWindow::GuiMainWindow() {
    init_window();
}

/**
 * Initialise the main window.
 */
void GuiMainWindow::init_window() {
    // uncomment for floating main window
    this->setWindowFlags(Qt::Dialog);

    QWidget *w_todo = new QWidget(this);
    QVBoxLayout *l_todo = new QVBoxLayout(w_todo);
    TodoListWidget *todo_list = new TodoListWidget(this);
    QPushButton *b_new_todo = new QPushButton("Add new to-do");
    l_todo->addWidget(todo_list);
    l_todo->addWidget(b_new_todo);

    QWidget *w_appt = new QWidget;
    QVBoxLayout *l_appt = new QVBoxLayout(w_appt);
    QPushButton *b_new_appt = new QPushButton("Add new appointment");
    l_appt->addWidget(b_new_appt);

    QTabWidget *tabber = new QTabWidget;
    tabber->addTab(w_todo, "To-dos");
    tabber->addTab(w_appt, "Appointments");

    connect(b_new_appt, SIGNAL(clicked()), this, SLOT(open_new_appt_dialog()));

    setCentralWidget(tabber);
}

void GuiMainWindow::open_new_appt_dialog() {
    log("opening new appt. dialog");
    NewApptDialog *w_appt_dialog = new NewApptDialog(this);
    if (w_appt_dialog->exec() == QDialog::Accepted) {
        log("adding new appointment");
        QString appt_title;
        QString appt_desc;
        w_appt_dialog->get_details(&appt_title, &appt_desc);

        db.insert_appt(
                    DBObject(appt_title.toUtf8().constData()),
                    DBObject(appt_desc.toUtf8().constData()) );
    }
    // we're finished with the window: delete it
    delete w_appt_dialog;
}
