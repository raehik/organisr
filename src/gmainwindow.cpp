#include "gmainwindow.h"

#include <vector>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QMenuBar>
#include <QMenu>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

#include "gnewapptdialog.h"
#include "gnewtododialog.h"
#include "gwinabout.h"
#include "gtodolistwidget.h"
#include "appointment.h"
#include "log.h"

using namespace Util;

QString GMainWindow::data_dir = QDir::toNativeSeparators(
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
            + "/digital-organiser");
QString GMainWindow::db_file = "test.db";

GMainWindow::GMainWindow() : db((QDir().mkpath(data_dir), QDir::toNativeSeparators(data_dir + "/" + db_file).toStdString()))
{
    init_window();
}

void GMainWindow::init_window() {
    // Window size/options {{{
    // uncomment for floating main window
    this->setWindowFlags(Qt::Dialog);
    this->setWindowTitle("Digital organiser");

    // fixed size
    resize(600, 480);
    // }}}

    // Menu bar {{{
    QMenu *m_new = menuBar()->addMenu(tr("&New"));
    QAction *a_new_appt = new QAction(tr("&Appointment"), this);
    QAction *a_new_todo = new QAction(tr("&To-do"), this);
    m_new->addAction(a_new_appt);
    m_new->addAction(a_new_todo);

    QMenu *m_search = menuBar()->addMenu(tr("&Search"));
    QAction *a_srch_appt = new QAction(tr("Search in &appointments"), this);
    QAction *a_srch_todo = new QAction(tr("Search in &to-dos"), this);
    m_search->addAction(a_srch_appt);
    m_search->addAction(a_srch_todo);

    QMenu *m_view = menuBar()->addMenu(tr("&View"));
    QAction *a_view_day = new QAction(tr("&Day"), this);
    QAction *a_view_month = new QAction(tr("&Month"), this);
    QAction *a_view_year = new QAction(tr("&Year"), this);
    QAction *a_view_todo = new QAction(tr("All &to-dos"), this);
    m_view->addAction(a_view_day);
    m_view->addAction(a_view_month);
    m_view->addAction(a_view_year);
    m_view->addSeparator();
    m_view->addAction(a_view_todo);

    QMenu *m_help = menuBar()->addMenu(tr("&Help"));
    QAction *a_manual = new QAction(tr("&User manual"), this);
    QAction *a_about = new QAction(tr("&About"), this);
    m_help->addAction(a_manual);
    m_help->addAction(a_about);
    // }}}

    // Menu bar sigs&slots {{{
    connect(a_new_appt, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));
    connect(a_new_todo, SIGNAL(triggered(bool)), this, SLOT(open_new_todo_dialog()));

    connect(a_srch_appt, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));
    connect(a_srch_todo, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));

    connect(a_view_day, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));
    connect(a_view_month, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));
    connect(a_view_year, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));
    connect(a_view_todo, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));

    connect(a_manual, SIGNAL(triggered(bool)), this, SLOT(open_new_appt_dialog()));
    connect(a_about, SIGNAL(triggered(bool)), this, SLOT(winopen_about()));
    // }}}

    // Window contents {{{
    QWidget *w_todo = new QWidget;
    QVBoxLayout *l_todo = new QVBoxLayout(w_todo);
    wid_todo = new GTodoListWidget(this);
    QPushButton *b_new_todo = new QPushButton("Add new to-do");
    l_todo->addWidget(wid_todo);
    l_todo->addWidget(b_new_todo);

    QWidget *w_appt = new QWidget;
    QVBoxLayout *l_appt = new QVBoxLayout(w_appt);
    QPushButton *b_new_appt = new QPushButton("Add new appointment");
    l_appt->addWidget(b_new_appt);

    QTabWidget *tabber = new QTabWidget;
    tabber->addTab(w_todo, "To-dos");
    tabber->addTab(w_appt, "Appointments");
    // }}}

    // Button sigs&slots {{{
    connect(b_new_appt, SIGNAL(clicked()), this, SLOT(open_new_appt_dialog()));
    connect(b_new_todo, SIGNAL(clicked()), this, SLOT(open_new_todo_dialog()));
    // }}}

    setCentralWidget(tabber);
}

void GMainWindow::open_new_appt_dialog() {
    log("opening new appt. dialog");
    GNewApptDialog *w_appt_dialog = new GNewApptDialog(this);
    if (w_appt_dialog->exec() == QDialog::Accepted) {
        QString appt_title;
        QString appt_desc;
        w_appt_dialog->get_details(&appt_title, &appt_desc);
        log("adding new appt " + (std::string)appt_title.toUtf8().constData());

        db.insert_appt(
                    DBObject(appt_title.toUtf8().constData()),
                    DBObject(appt_desc.toUtf8().constData()) );
    }
    // we're finished with the window: delete it
    delete w_appt_dialog;
}

void GMainWindow::open_new_todo_dialog() {
    log("opening new dialog");
    GNewTodoDialog *w_dialog = new GNewTodoDialog(this);
    if (w_dialog->exec() == QDialog::Accepted) {
        QString todo_text;
        w_dialog->get_details(&todo_text);
        log("adding new todo " + (std::string)todo_text.toUtf8().constData());

        db.insert_todo(todo_text.toUtf8().constData());
    }
    // we're finished with the window: delete it
    delete w_dialog;

    // now update the todo dialog
    wid_todo->refresh();
}

std::vector<std::string> GMainWindow::get_todos() {
    log("getting all todos");
    return db.get_todos();
}

void GMainWindow::winopen_about() {
    GWinAbout *win = new GWinAbout(this);
    win->exec();
}
