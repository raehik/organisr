#ifndef NEWAPPTDIALOG_H
#define NEWAPPTDIALOG_H

#include <QApplication>
#include <QWidget>

class NewApptDialog : public QWidget
{

    Q_OBJECT

public:
    NewApptDialog(QWidget *parent = 0);
    virtual ~NewApptDialog() {};

private:
    void init_window();

private slots:
    void accepted();
    void cancelled();
};

#endif // NEWAPPTDIALOG_H
