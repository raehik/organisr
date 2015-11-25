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

    // do logic stuff
    DataHandler db = DataHandler();
    std::vector<Appointment> appts;
    appts.push_back(Appointment("test title 1", "test desc 1"));
    db.insert_appts(appts);

    return app.exec();
}
