#ifndef GWINVIEWAPPTMONTH_H
#define GWINVIEWAPPTMONTH_H

#include <QDialog>
#include <QDate>
#include <QGridLayout>
#include "datahandler.h"


class GWinViewApptMonth : public QDialog
{
    Q_OBJECT

public:
    GWinViewApptMonth(QDate date, DataHandler *db, QWidget *parent);
    void init_window();
    int refresh();

private:
    void make_printout();

    DataHandler *db;
    QGridLayout *day_grid;
    QDate date;
    QWidget *grid_widget;

    const static int CAL_WIDTH;
    const static int WIN_X;
    const static int WIN_Y;
};

#endif // GWINVIEWAPPTMONTH_H
