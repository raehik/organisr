#ifndef GTODOLISTWIDGET_H
#define GTODOLISTWIDGET_H

#include <vector>
#include <string>
#include <QTextList>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "datahandler.h"


class GTodoListWidget : public QWidget
{
public:
    GTodoListWidget(DataHandler *db, QWidget *parent = 0);
    void build_widget();

    /**
     * \brief Get to-dos and update the widget display.
     */
    void refresh();

private:
    QVBoxLayout *top_layout;
    QLabel *todos_label;

    DataHandler *db;

    void delete_todo(RecTodo todo);
    void edit_todo(RecTodo todo);
    void toggle_complete(RecTodo todo);
};

#endif // GTODOLISTWIDGET_H
