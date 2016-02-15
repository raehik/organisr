#include "gmainwindow.h"

#include <vector>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QMenuBar>
#include <QMenu>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QDir>
#include <QCoreApplication>

#include "gnewapptdialog.h"
#include "gnewtododialog.h"
#include "gwinabout.h"
#include "gwinviewday.h"
#include "gtodolistwidget.h"
#include "log.h"

using namespace Util;

QString GMainWindow::data_dir = QDir::toNativeSeparators(
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
            + "/digital-organiser");
QString GMainWindow::db_file = "test.db";

QString manual_file = "manual.pdf";

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
    connect(a_new_appt, &QAction::triggered, this, &GMainWindow::open_new_appt_dialog);
    connect(a_new_todo, &QAction::triggered, this, &GMainWindow::open_new_todo_dialog);

    connect(a_srch_appt, &QAction::triggered, this, &GMainWindow::open_new_appt_dialog);
    connect(a_srch_todo, &QAction::triggered, this, &GMainWindow::open_new_appt_dialog);

    connect(a_view_day, &QAction::triggered, this, &GMainWindow::winopen_view_day);
    connect(a_view_month, &QAction::triggered, this, &GMainWindow::open_new_appt_dialog);
    connect(a_view_year, &QAction::triggered, this, &GMainWindow::open_new_appt_dialog);
    connect(a_view_todo, &QAction::triggered, this, &GMainWindow::open_new_appt_dialog);

    connect(a_manual, &QAction::triggered, [](){
        QDesktopServices::openUrl(QUrl(QDir::toNativeSeparators(data_dir + "/" + manual_file)));
    });
    connect(a_about, &QAction::triggered, this, &GMainWindow::winopen_about);
    // }}}

    // Window contents {{{
    QWidget *w_todo = new QWidget;
    QVBoxLayout *l_todo = new QVBoxLayout(w_todo);
    wid_todo = new GTodoListWidget(&db, this);
    QPushButton *b_new_todo = new QPushButton("&Add new to-do");
    l_todo->addWidget(wid_todo);
    l_todo->addWidget(b_new_todo);

    QWidget *w_appt = new QWidget;
    QVBoxLayout *l_appt = new QVBoxLayout(w_appt);
    QPushButton *b_new_appt = new QPushButton("&Add new appointment");
    l_appt->addWidget(b_new_appt);

    QTabWidget *tabber = new QTabWidget;
    tabber->addTab(w_todo, "To-dos");
    tabber->addTab(w_appt, "Appointments");
    // }}}

    // Button sigs&slots {{{
    connect(b_new_appt, &QPushButton::clicked, this, &GMainWindow::open_new_appt_dialog);
    connect(b_new_todo, &QPushButton::clicked, this, &GMainWindow::open_new_todo_dialog);
    // }}}

    setCentralWidget(tabber);
}

void GMainWindow::open_new_appt_dialog() {
    log("opening new appt. dialog");
    GNewApptDialog *w_appt_dialog = new GNewApptDialog(this);
    if (w_appt_dialog->exec() == QDialog::Accepted) {
        QString appt_title;
        QString appt_desc;
        QDate appt_date;
        QTime appt_time;
        QString appt_loc;
        w_appt_dialog->get_details(&appt_title, &appt_desc, &appt_date, &appt_time, &appt_loc);
        log("adding new appt " + appt_title.toUtf8().toStdString());
        db.insert_appt(
                    DataObject(appt_title.toUtf8().toStdString()),
                    DataObject(appt_desc.toUtf8().toStdString()),
                    DataObject(appt_date.toJulianDay()),
                    DataObject(QTime(0, 0, 0).secsTo(appt_time)),
                    DataObject(appt_loc.toUtf8().toStdString())
                   );
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

void GMainWindow::winopen_about() {
    GWinAbout *win = new GWinAbout(this);
    win->exec();
}

void GMainWindow::winopen_view_day() {
    GWinViewDay *win = new GWinViewDay(&db, this);
    win->show();
}
