#include <QApplication>
#include "guihandler.h"
#include "datahandler.h"
#include "gmainwindow.h"

GuiHandler::GuiHandler() {
}

int GuiHandler::init(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // start GUI
    GMainWindow *main_win = new GMainWindow();

    // show when we do app.exec()
    main_win->show();

    return app.exec();
}
