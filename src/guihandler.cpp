#include <QApplication>
#include "guihandler.h"
#include "ui_mainwindow.h"
#include "datahandler.h"

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
    QMainWindow *main_win = new QMainWindow;
    Ui::MainWindow ui;
    ui.setupUi(main_win);
    main_win->show();

    // do logic stuff
    DataHandler db = DataHandler();
    std::vector<Appointment> appts;
    appts.push_back(Appointment("test title 1", "test desc 1"));
    db.insert_appts(appts);

    //LayoutHandler layout;
    //layout.init_layout();

    return app.exec();
}
