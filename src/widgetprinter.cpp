#include "widgetprinter.h"

#include <QPrintDialog>
#include <QPainter>
#include "log.h"

WidgetPrinter::WidgetPrinter(QWidget *print_object, QString dialog_title) :
    printer(QPrinter::HighResolution)
{
    this->print_object = print_object;

    opt_dialog_title = dialog_title;
    printer_filename = "calendar.pdf";

    // set default options so that dialog needs less changing by default
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(printer_filename);
}

void WidgetPrinter::dialogAndPrint() {
    QPrintDialog *print_dialog = new QPrintDialog(&printer, this);
    print_dialog->setWindowTitle(opt_dialog_title);

    if(print_dialog->exec() == QDialog::Accepted) {
        QPainter painter;
        painter.begin(&printer);

        // scale to full page (thanks to http://doc.qt.io/qt-4.8/printing.html )
        double xscale = printer.pageRect().width()/double(print_object->width());
        double yscale = printer.pageRect().height()/double(print_object->height());
        double scale = qMin(xscale, yscale);
        painter.scale(scale, scale);
        print_object->render(&painter);
        painter.end();

        Util::log("printed");
    }
    delete print_dialog;
}
