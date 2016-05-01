#ifndef GWINSEARCHAPPT_H
#define GWINSEARCHAPPT_H

#include "recappt.h"

#include "datahandler.h"

#include <QWidget>
#include <QDialog>
#include <QString>
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
    void get_details(QString *title_ptr, QString *desc_ptr, QDate *date_ptr, QTime *time_ptr, QString *loc_ptr);

private:
    QLineEdit *field_title;
    QTextEdit *field_desc;
    QCalendarWidget *field_date;
    QLineEdit *field_loc;
    QTimeEdit *field_time;
    QLabel *label_title;
    QLabel *label_desc;
    QLabel *label_date;
    QLabel *label_time;
    QLabel *label_loc;

    void init_window();
    void run_search();
};

#endif // GWINSEARCHAPPT_H
