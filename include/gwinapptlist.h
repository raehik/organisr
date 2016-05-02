#ifndef GWINAPPTLIST_H
#define GWINAPPTLIST_H

#include <QDialog>
#include <QWidget>

#include <vector>
#include "recappt.h"


class GWinApptList : public QDialog
{
    Q_OBJECT

public:
    GWinApptList();
    GWinApptList(std::vector<RecAppt> appts, QWidget *parent);

private:
    void init_window();
    std::vector<RecAppt> appts;
};

#endif // GWINAPPTLIST_H
