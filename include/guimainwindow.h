#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QMainWindow>
#include "newapptdialog.h"

class GuiMainWindow : public QMainWindow
{

    Q_OBJECT

public:
    GuiMainWindow();
    void init_window();

private slots:
    void open_new_appt_dialog();

private:
    NewApptDialog* _new_appt_dialog;
};

#endif // GUIMAINWINDOW_H
