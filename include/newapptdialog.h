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
    QLineEdit *field_title;
    QTextEdit *field_desc;
    void init_window();
    bool field_not_empty(QString field_text);
};

#endif // NEWAPPTDIALOG_H
