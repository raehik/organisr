#ifndef GAPPTDAYWIDGET_H
#define GAPPTDAYWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "datahandler.h"

/**
 * \brief A QT window for viewing a single day's appointments.
 */
class GApptDayWidget : public QWidget
{
    Q_OBJECT

public:
    GApptDayWidget(DataHandler *db, QWidget *parent = 0);
    void init_window();
    int refresh();
    void print_window();

private:
    /// Test
    const static int W_CAL;
    const static int H_CAL;
    const static int W_APPTS;

    DataHandler *db;
    QCalendarWidget *cal;
    QGridLayout *grid;
    std::vector<QWidget*> cur_appts;

    void edit_appt(RecAppt appt);
};

#endif // GAPPTDAYWIDGET_H
