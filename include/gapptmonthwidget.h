#ifndef GAPPTMONTHWIDGET_H
#define GAPPTMONTHWIDGET_H

#include <QDialog>
#include <QDate>
#include <QGridLayout>
#include "datahandler.h"


class GApptMonthWidget : public QDialog
{
    Q_OBJECT

public:
    GApptMonthWidget(QDate date, DataHandler *db, QWidget *parent);
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

#endif // GAPPTMONTHWIDGET_H
