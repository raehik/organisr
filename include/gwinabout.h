#ifndef GWINABOUT_H
#define GWINABOUT_H

#include <QDialog>
#include <QWidget>


class GWinAbout : public QDialog
{
    Q_OBJECT

public:
    GWinAbout(QWidget *parent = 0);
    void init_win();
};

#endif // GWINABOUT_H
