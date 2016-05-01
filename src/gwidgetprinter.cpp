#include "gwidgetprinter.h"

#include <QPrintDialog>
#include <QPainter>
#include "log.h"

using namespace Util;

GWidgetPrinter::GWidgetPrinter(QWidget *print_object, QString dialog_title, bool landscape) :
    printer(QPrinter::HighResolution)
{
    this->print_object = print_object;

    opt_dialog_title = dialog_title;
    printer_filename = "calendar.pdf";

    /// We set some default options so that the user may not need to change them
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(printer_filename);
    if (landscape) {
        printer.setOrientation(QPrinter::Landscape);
    }
}

void GWidgetPrinter::dialogAndPrint() {
    log("starting print dialog");

    QPrintDialog *print_dialog = new QPrintDialog(&printer, this);
    print_dialog->setWindowTitle(opt_dialog_title);

    if(print_dialog->exec() == QDialog::Accepted) {
        log("print dialog: accepted, printing");
        QPainter painter;
        painter.begin(&printer);

        /// scale to full page (thanks to http://doc.qt.io/qt-4.8/printing.html )
        double xscale = printer.pageRect().width()/double(print_object->width());
        double yscale = printer.pageRect().height()/double(print_object->height());
        double scale = qMin(xscale, yscale);
        painter.scale(scale, scale);
        print_object->render(&painter);
        painter.end();
    } else {
        log("print dialog: cancelled");
    }
}
