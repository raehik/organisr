#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include "guihandler.h"
#include "datahandler.h"

/**
 * @brief The initial 'x' (left-right) size of the main window.
 */
int GuiHandler::initial_win_x = 400;

/**
 * @brief The initial 'y' (up-down) size of the main window.
 */
int GuiHandler::initial_win_y = 300;

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

    main_win.setFixedSize(initial_win_x, initial_win_y);

    QPushButton *button = new QPushButton("ayy lmao", &main_win);
    int b_x = 80;
    int b_y = 30;
    int y_offset = 10;
    button->setGeometry((initial_win_x - b_x)/2,
                        initial_win_y - y_offset - b_y,
                        b_x,
                        b_y);

    main_win.show();

    DataHandler db = DataHandler();
    std::vector<Appointment> appts;
    appts.push_back(Appointment("test title 1", "test desc 1"));
    db.insert_appts(appts);

    return app.exec();
}

void GuiHandler::init_layout() {
    QGridLayout *grid = new QGridLayout(&main_win);
    main_win.setLayout(grid);
}
