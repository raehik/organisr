#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QWidget>
#include <QApplication>


class GuiHandler
{
public:
    GuiHandler();
    int init(int argc, char *argv[]);
    void init_layout();

    static int initial_win_x;
    static int initial_win_y;
private:
    QApplication app(int argc, char* argv[]);
    QWidget main_win;
};

#endif // GUIHANDLER_H
