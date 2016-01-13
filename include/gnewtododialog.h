#ifndef GNEWTODODIALOG_H
#define GNEWTODODIALOG_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>

class GNewTodoDialog : public QDialog
{

    Q_OBJECT

public:
    GNewTodoDialog(QWidget *parent = 0);
    virtual ~GNewTodoDialog() {}
    void get_details(QString *text_ptr);

public slots:
    int verify_fields();

private:
    QLineEdit *field_text;
    QLabel *label_text;
    void init_window();
    bool field_not_empty(QString field_text, QString field_name);
};

#endif // GNEWTODODIALOG_H
