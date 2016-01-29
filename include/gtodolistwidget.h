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

    /**
     * \brief Get to-dos and update the widget display.
     */
    void refresh();

private:
    QLabel *todos_label;

    /// A bit unneat, but we require a pointer to a GMainWindow to access get_todos()
    GMainWindow *parent_win;
};

#endif // GTODOLISTWIDGET_H
