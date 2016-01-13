#include "gtodolistwidget.h"
#include "gmainwindow.h"
#include <QTextEdit>
#include <string>
#include <QString>
#include <QLabel>
#include <QBoxLayout>


#include "log.h"

using namespace Util;

GTodoListWidget::GTodoListWidget(GMainWindow *parent) : QWidget(parent) {
    this->parent_win = parent;
    build_widget();
}

void GTodoListWidget::build_widget() {
    // make & set layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    todos_label = new QLabel;
    //todos_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    todos_label->setWordWrap(true);
    layout->addWidget(todos_label);
    this->setLayout(layout);
    refresh();
}

void GTodoListWidget::refresh() {
    log("refreshing todos");
    std::vector<std::string> todos = parent_win->get_todos();
    std::string todo_text = "<h2>To-dos</h2>";
    // add each todo in sequence if there are any
    if (todos.size() > 0) {
        todo_text += "<p><ul>";
        for (std::vector<std::string>::size_type i = 0; i != todos.size(); i++) {
            // HTML escape to-dos for safety
            std::string todo_formatted = QString::fromStdString(
                        todos[i]).toHtmlEscaped().toUtf8().toStdString();
            std::string tmp = "<li>" + todo_formatted + "</li>";
            todo_text += tmp;
        }
    // override if there were no todos
    } else {
        todo_text += "<p>No to-dos!</p>";
    }
    todos_label->setText(QString::fromStdString(todo_text));
}
