#ifndef GNEWAPPTDIALOG_H
#define GNEWAPPTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCalendarWidget>

class GNewApptDialog : public QDialog
{
    Q_OBJECT

public:
    GNewApptDialog(QWidget *parent = 0);
    virtual ~GNewApptDialog() {}
    void get_details(QString *title_ptr, QString *desc_ptr, QDate *date_ptr, QString *loc_ptr);

public slots:
    int verify_fields();

private:
    QLineEdit *field_title;
    QTextEdit *field_desc;
    QCalendarWidget *field_date;
    QLineEdit *field_loc;
    QLabel *label_title;
    QLabel *label_desc;
    QLabel *label_date;
    QLabel *label_loc;
    void init_window();
    bool field_not_empty(QString field_text, QString field_name);
};

#endif // GNEWAPPTDIALOG_H
