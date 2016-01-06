#ifndef GTODOLISTWIDGET_H
#define GTODOLISTWIDGET_H

#include <QTextList>
#include <QWidget>


class GTodoListWidget : public QWidget
{
public:
    GTodoListWidget(QWidget *parent = 0);
    void build_widget();
};

#endif // GTODOLISTWIDGET_H
