#ifndef LAYOUTHANDLER_H
#define LAYOUTHANDLER_H

#include <QWidget>

class LayoutHandler {
    public:
        LayoutHandler();

        void init_layout();

        static int initial_win_x;
        static int initial_win_y;

    private:
        QWidget main_win;
};

#endif // LAYOUTHANDLER_H
