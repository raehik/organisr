#include "gtodolistwidget.h"
#include <QTextEdit>
#include <QPalette>
#include <QLabel>

GTodoListWidget::GTodoListWidget(QWidget *parent) : QWidget(parent) {
    build_widget();
}

void GTodoListWidget::build_widget() {
    QLabel *text = new QLabel("<h2>To-dos</h2><p><ul><li>wow</li></ul></p>", this);
}
