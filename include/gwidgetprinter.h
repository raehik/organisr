#ifndef GWIDGETPRINTER_H
#define GWIDGETPRINTER_H

#include <QWidget>
#include <QPrinter>
#include <QString>

class GWidgetPrinter : public QWidget
{
public:
    GWidgetPrinter(QWidget *print_object, QString dialog_title);
    void dialogAndPrint();

private:
    QWidget *print_object;
    QPrinter printer;
    QString opt_dialog_title;
    QString printer_filename;
};

#endif // GWIDGETPRINTER_H
