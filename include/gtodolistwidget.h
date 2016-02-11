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

    /// A bit unneat, but we require a pointer to a GMainWindow to access get_todos()
    DataHandler *db;

    void delete_todo(int id);
    void edit_todo(int id, std::string cur_text);
    void complete_todo(int id);
};

#endif // GTODOLISTWIDGET_H
