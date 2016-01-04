#include "guimainwindow.h"

#include <vector>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QMenuBar>
#include <QMenu>

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
    // Window size/options {{{
    // uncomment for floating main window
    this->setWindowFlags(Qt::Dialog);

    // fixed size
    resize(600, 480);
    // }}}

    // Menu bar {{{
    QMenu *m_new = menuBar()->addMenu(tr("&New"));
    QAction *a_new_appt = new QAction("&Appointment", this);
    QAction *a_new_todo = new QAction("&To-do", this);
    m_new->addAction(a_new_appt);
    m_new->addAction(a_new_todo);

    QMenu *m_search = menuBar()->addMenu(tr("&Search"));
    QAction *a_srch_appt = new QAction("Search in &appointments", this);
    QAction *a_srch_todo = new QAction("Search in &to-dos", this);
    m_search->addAction(a_srch_appt);
    m_search->addAction(a_srch_todo);

    QMenu *m_view = menuBar()->addMenu(tr("&View"));
    QAction *a_view_day = new QAction("&Day", this);
    QAction *a_view_month = new QAction("&Month", this);
    QAction *a_view_year = new QAction("&Year", this);
    QAction *a_view_todo = new QAction("All &to-dos", this);
    m_view->addAction(a_view_day);
    m_view->addAction(a_view_month);
    m_view->addAction(a_view_year);
    m_view->addSeparator();
    m_view->addAction(a_view_todo);

    QMenu *m_help = menuBar()->addMenu(tr("&Help"));
    QAction *a_manual = new QAction("&User manual", this);
    QAction *a_about = new QAction("&About", this);
    m_help->addAction(a_manual);
    m_help->addAction(a_about);
    // }}}

    // Window contents {{{
    QWidget *w_todo = new QWidget;
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
    // }}}

    // Signals & slots {{{
    connect(b_new_appt, SIGNAL(clicked()), this, SLOT(open_new_appt_dialog()));
    // }}}

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
