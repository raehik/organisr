#ifndef GWIDGETPRINTER_H
#define GWIDGETPRINTER_H

#include <QWidget>
#include <QPrinter>
#include <QString>

class GWidgetPrinter : public QWidget
{
public:
    GWidgetPrinter(QWidget *print_object, QString dialog_title);

    /**
     * \brief Present an option dialog and print depending on input.
     *
     * The user is presented with a QPrintDialog which allows them to choose
     * whether to print to a physical printer & options to do so, or export to a
     * PDF file. Whatever print_object was provided in the constructor is scaled
     * to a full page before printing.
     */
    void dialogAndPrint();

private:
    QWidget *print_object;
    QPrinter printer;
    QString opt_dialog_title;
    QString printer_filename;
};

#endif // GWIDGETPRINTER_H
