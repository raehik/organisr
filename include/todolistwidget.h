#ifndef TODOLISTWIDGET_H
#define TODOLISTWIDGET_H

#include <QTextList>
#include <QWidget>


class TodoListWidget : public QWidget
{
public:
    TodoListWidget(QWidget *parent = 0);
    void build_widget();
};

#endif // TODOLISTWIDGET_H
