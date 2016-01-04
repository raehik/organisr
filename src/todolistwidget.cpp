#include "todolistwidget.h"
#include <QTextEdit>
#include <QPalette>
#include <QLabel>

TodoListWidget::TodoListWidget(QWidget *parent) : QWidget(parent) {
    build_widget();
}

void TodoListWidget::build_widget() {
    QLabel *text = new QLabel("<h2>To-dos</h2><p><ul><li>wow</li></ul></p>", this);
}
