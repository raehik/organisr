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
     * \brief Fetch to-dos from database and update the widget display.
     */
    void refresh();

    /**
     * \brief Print the current list of to-dos to a printer or PDF.
     */
    void print_list();

private:
    QVBoxLayout *top_layout;
    QLabel *todos_label;

    DataHandler *db;

    void delete_todo(RecTodo todo);
    void edit_todo(RecTodo todo);
    void toggle_complete(RecTodo todo);
};

#endif // GTODOLISTWIDGET_H
