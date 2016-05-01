#ifndef GWINVIEWDAY_H
#define GWINVIEWDAY_H

#include "recappt.h"

#include <QWidget>
#include <QDialog>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "datahandler.h"

/**
 * \brief A QT window for viewing a single day's appointments.
 */
class GWinViewDay : public QDialog
{
    Q_OBJECT

public:
    GWinViewDay(DataHandler *db, QWidget *parent = 0);
    void init_window();
    int update_appts();
    void edit_appt(RecAppt appt);
    void print_widget();

private:
    /// Pointer to the database handler. Used for retrieving appointments.
    DataHandler *db;

    QCalendarWidget *cal;
    QGridLayout *grid;
    std::vector<QWidget*> cur_appts;

    const static int W_CAL;
    const static int H_CAL;
    const static int W_APPTS;
};

#endif // GWINVIEWDAY_H
