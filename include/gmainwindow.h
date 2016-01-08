#ifndef GMAINWINDOW_H
#define GMAINWINDOW_H

#include "datahandler.h"
#include "gwinabout.h"
#include <QMainWindow>
#include "gnewapptdialog.h"

class GMainWindow : public QMainWindow
{

    Q_OBJECT

public:
    GMainWindow();

private slots:
    void open_new_appt_dialog();
    void winopen_about();

private:
    DataHandler db;
    void init_window();
    GNewApptDialog* _new_appt_dialog;
};

#endif // GMAINWINDOW_H
