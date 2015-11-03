#include <QApplication>
#include "guihandler.h"
#include "layouthandler.h"

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

    LayoutHandler layout;
    layout.init_layout();

    return app.exec();
}
