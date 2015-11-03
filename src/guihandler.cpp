#include "guihandler.h"

/**
 * @brief The initial 'x' (left-right) size of the main window.
 */
int GuiHandler::initial_win_x = 400;

/**
 * @brief The initial 'y' (up-down) size of the main window.
 */
int GuiHandler::initial_win_y = 400;

GuiHandler::GuiHandler() {
}

/**
 * @brief Initialise the GUI.
 *
 * We do this before connecting to the database so that we can display errors
 * using the GUI.
 */
void GuiHandler::init() {
    int y_offset = 10;

    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(w_x, w_y);

    QPushButton *button = new QPushButton("ayy lmao", &window);
    int b_x = 80;
    int b_y = 30;
    button->setGeometry((initial_win_x - b_x)/2,
                        initial_win_x - y_offset - b_y,
                        b_x,
                        b_y);

    window.show();

    DataHandler db = DataHandler();
    std::vector<Appointment> appts;
    appts.push_back(Appointment("test title 1", "test desc 1"));
    db.insert_appts(appts);

    return app.exec();
}
