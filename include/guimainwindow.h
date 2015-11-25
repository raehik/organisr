#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QMainWindow>
#include "newapptdialog.h"

class GuiMainWindow : public QMainWindow
{

    Q_OBJECT

public:
    GuiMainWindow();

private slots:
    void open_new_appt_dialog();

private:
    void init_window();
    NewApptDialog* _new_appt_dialog;
};

#endif // GUIMAINWINDOW_H
