#ifndef NEWAPPTDIALOG_H
#define NEWAPPTDIALOG_H

#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>

class NewApptDialog : public QDialog
{

    Q_OBJECT

public:
    NewApptDialog(QWidget *parent = 0);
    virtual ~NewApptDialog() {};
    void get_details(QString *title_ptr, QString *desc_ptr);

public slots:
    int verify_fields();

private:
    void init_window();
    void finished(int result);
    QLineEdit *field_title;
    QTextEdit *field_desc;
};

#endif // NEWAPPTDIALOG_H
