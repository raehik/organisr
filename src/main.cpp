#include <QApplication>
#include <QPushButton>
#include "datahandler.h"

int main(int argc, char *argv[]) {
    int w_x = 400;
    int w_y = 300;
    int y_offset = 10;

    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(w_x, w_y);

    QPushButton *button = new QPushButton("ayy lmao", &window);
    int b_x = 80;
    int b_y = 30;
    button->setGeometry((w_x - b_x)/2, w_y - y_offset - b_y, b_x, b_y);

    window.show();

    DataHandler db = DataHandler();
    //db_helper.add_appt("Appt. title", "Long appointment description, including keywords");

    return app.exec();
}
