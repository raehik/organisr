#ifndef GTODOLISTWIDGET_H
#define GTODOLISTWIDGET_H

#include <datahandler.h>
//#include "gmainwindow.h"
// forward declaration
class GMainWindow;

#include <vector>
#include <string>
#include <QTextList>
#include <QLabel>
#include <QWidget>


class GTodoListWidget : public QWidget
{
public:
    GTodoListWidget(GMainWindow *parent = 0);
    void build_widget();
    void refresh();

private:
    QLabel *todos_label;
    GMainWindow *parent_win;
};

#endif // GTODOLISTWIDGET_H
