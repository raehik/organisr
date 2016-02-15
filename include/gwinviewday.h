#ifndef GWINVIEWDAY_H
#define GWINVIEWDAY_H

#include <QWidget>
#include <QDialog>
#include "datahandler.h"

class GWinViewDay : public QDialog
{
    Q_OBJECT

public:
    GWinViewDay(DataHandler *db, QWidget *parent = 0);
    void init_window();

private:
    DataHandler *db;
};

#endif // GWINVIEWDAY_H
