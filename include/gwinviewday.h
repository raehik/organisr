#ifndef GWINVIEWDAY_H
#define GWINVIEWDAY_H

#include <QWidget>
#include <QDialog>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "datahandler.h"

class GWinViewDay : public QDialog
{
    Q_OBJECT

public:
    GWinViewDay(DataHandler *db, QWidget *parent = 0);
    void init_window();
    int update_appts();

private:
    DataHandler *db;
    QCalendarWidget *cal;
    QGridLayout *grid;
    QHBoxLayout *layout;
    std::vector<QWidget*> cur_appts;
};

#endif // GWINVIEWDAY_H
