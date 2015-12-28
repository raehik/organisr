#ifndef WIDGETPRINTER_H
#define WIDGETPRINTER_H

#include <QWidget>
#include <QPrinter>

class WidgetPrinter : public QWidget
{
public:
    WidgetPrinter(QWidget *print_object, QString dialog_title);
    void dialogAndPrint();

private:
    QWidget *print_object;
    QPrinter printer;
    QString opt_dialog_title;
    QString printer_filename;
};

#endif // WIDGETPRINTER_H
