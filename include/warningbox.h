#ifndef WARNINGBOX_H
#define WARNINGBOX_H

#include <QMessageBox>
#include <QString>

class WarningBox : public QMessageBox
{

    Q_OBJECT

public:
    WarningBox(QString title, QString text, QWidget *parent = 0);
    virtual ~WarningBox() {};

private:
    void init_window();
};

#endif // WARNINGBOX_H
