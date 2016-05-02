#ifndef GWINSEARCHAPPT_H
#define GWINSEARCHAPPT_H

#include "recappt.h"

#include "datahandler.h"

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimeEdit>
#include <QCalendarWidget>

class GWinSearchAppt : public QDialog
{
    Q_OBJECT

public:
    GWinSearchAppt(DataHandler *db, QWidget *parent);

private:
    /// Pointer to the database handler. Used for retrieving appointments.
    DataHandler *db;

    QLabel *l_title;
    QLineEdit *f_title;
    QLabel *l_date_before;
    QCalendarWidget *f_date_before;
    QLabel *l_date_after;
    QCalendarWidget *f_date_after;
    QLabel *l_loc;
    QLineEdit *f_loc;

    void init_window();
    void run_search();
};

#endif // GWINSEARCHAPPT_H
