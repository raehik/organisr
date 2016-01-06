#ifndef GMAINWINDOW_H
#define GMAINWINDOW_H

#include "datahandler.h"
#include <QMainWindow>
#include "gnewapptdialog.h"

class GMainWindow : public QMainWindow
{

    Q_OBJECT

public:
    GMainWindow();

private slots:
    void open_new_appt_dialog();

private:
    DataHandler db;
    void init_window();
    GNewApptDialog* _new_appt_dialog;
};

#endif // GMAINWINDOW_H
