#include "gtodolistwidget.h"
#include "gmainwindow.h"
#include <QTextEdit>
#include <string>
#include <QString>
#include <QLabel>
#include <QTextDocument>

#include "log.h"

using namespace Util;

GTodoListWidget::GTodoListWidget(GMainWindow *parent) : QWidget(parent) {
    this->parent_win = parent;
    build_widget();
}

void GTodoListWidget::build_widget() {
    todos_label = new QLabel(this);
    todos_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    todos_label->setWordWrap(true);
    refresh();
}

void GTodoListWidget::refresh() {
    log("refreshing todos");
    std::vector<std::string> todos = parent_win->get_todos();
    std::string todo_text = "<h2>To-dos</h2><p><ul>";
    for (std::vector<std::string>::size_type i = 0; i != todos.size(); i++) {
        log(todos[i]);
        std::string tmp = "<li>" + todos[i] + "</li>";
        todo_text += tmp;
    }
    todo_text += "</ul></p>";
    //todos_label->setText(QString::fromStdString(todo_text));
}
