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

    QGridLayout *grid = new QGridLayout(&main_win);
    main_win.setLayout(grid);
}
