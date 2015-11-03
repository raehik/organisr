#include "layouthandler.h"
#include "datahandler.h"
#include <QPushButton>
#include <QGridLayout>

/**
 * @brief The initial 'x' (left-right) size of the main window.
 */
int LayoutHandler::initial_win_x = 400;

/**
 * @brief The initial 'y' (up-down) size of the main window.
 */
int LayoutHandler::initial_win_y = 300;

LayoutHandler::LayoutHandler() {
}

void LayoutHandler::init_layout() {
    // add a button
    int b_x = 80;
    int b_y = 30;
    int y_offset = 10;
    QPushButton *button = new QPushButton("ayy lmao", &main_win);
    button->setGeometry((initial_win_x - b_x)/2,
                        initial_win_y - y_offset - b_y,
                        b_x,
                        b_y);

    // do logic stuff
    DataHandler db = DataHandler();
    std::vector<Appointment> appts;
    appts.push_back(Appointment("test title 1", "test desc 1"));
    db.insert_appts(appts);

    // set main window layout
    QGridLayout *grid = new QGridLayout(&main_win);
    main_win.setLayout(grid);

    // show the main window
    main_win.setFixedSize(initial_win_x, initial_win_y);
    main_win.show();
    main_win.setLayout(grid);
}
