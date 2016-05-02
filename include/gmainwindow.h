#ifndef GMAINWINDOW_H
#define GMAINWINDOW_H

#include <vector>
#include <string>

#include "datahandler.h"
#include "gwinabout.h"
#include <QMainWindow>
#include "gnewapptdialog.h"
#include "gtodolistwidget.h"
#include "gapptdaywidget.h"

class GMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GMainWindow();

private slots:
    void open_new_appt_dialog();
    void open_new_todo_dialog();
    void winopen_about();
    void winopen_view_month();
    void winopen_search_appt();

private:
    DataHandler db;

    static QString data_dir;
    static QString db_file;
    GTodoListWidget *wid_todo;
    GApptDayWidget *wid_appt;

    /**
     * \brief Initialise the main window.
     */
    void init_window();
};

#endif // GMAINWINDOW_H
