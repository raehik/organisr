#include <QApplication>
#include "guihandler.h"
#include "datahandler.h"
#include "guimainwindow.h"

GuiHandler::GuiHandler() {
}

/**
 * @brief Initialise the GUI.
 *
 * We do this before connecting to the database so that we can display errors
 * using the GUI.
 */
int GuiHandler::init(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // start GUI
    GuiMainWindow *main_win = new GuiMainWindow();

    // show when we do app.exec()
    main_win->show();

    return app.exec();
}
