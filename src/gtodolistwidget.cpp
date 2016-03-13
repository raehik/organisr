#include "gtodolistwidget.h"
#include "gmainwindow.h"
#include "rectodo.h"
#include <QTextEdit>
#include <string>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>
#include "gnewtododialog.h"


#include "log.h"

using namespace Util;

GTodoListWidget::GTodoListWidget(DataHandler *db, QWidget *parent) : QWidget(parent) {
    this->db = db;
    build_widget();
}

void GTodoListWidget::build_widget() {
    log("initialising todo list widget");
    refresh();
}

void GTodoListWidget::refresh() {
    log("refreshing todos");

    // clear current state
    qDeleteAll(this->children());

    // get todos
    std::vector<RecTodo> todos = db->get_todos();

    // init layout
    QVBoxLayout *l_main = new QVBoxLayout;
    l_main->setAlignment(Qt::AlignTop);

    QVBoxLayout *l_todo = new QVBoxLayout;
    l_todo->setAlignment(Qt::AlignTop);
    l_todo->addWidget(new QLabel("<h2>To-dos</h2>"));

    QVBoxLayout *l_done = new QVBoxLayout;
    l_todo->setAlignment(Qt::AlignTop);

    // add each todo in sequence if there are any
    if (todos.size() > 0) {
        for (std::vector<RecTodo>::size_type i = 0; i != todos.size(); i++) {
            RecTodo todo = todos[i];

            // get & format to-do (HTML escape for safety)
            std::string fmt_str = "<p style='font-size: 10pt'>&bull; ";
            if (todo.done) {
                // if done, strikethrough
                fmt_str += "<s>";
            }
            std::string todo_str = QString::fromStdString(
                            todo.text).toHtmlEscaped().toUtf8().toStdString();
            fmt_str += todo_str + "</p>";
            if (todo.done) {
                // end done strikethrough
                fmt_str += "</s>";
            }

            // add delete/edit buttons
            QPushButton *b_del_cur = new QPushButton("X");
            QPushButton *b_edit_cur = new QPushButton("E");
            QPushButton *b_toggle_cur = new QPushButton("✓");

            b_del_cur->setMinimumWidth(20);
            b_edit_cur->setMinimumWidth(20);
            b_toggle_cur->setMinimumWidth(20);

            connect(b_del_cur, &QPushButton::clicked, this, [this, todo](){ delete_todo(todo); });
            connect(b_edit_cur, &QPushButton::clicked, this, [this, todo](){ edit_todo(todo); });
            connect(b_toggle_cur, &QPushButton::clicked, this, [this, todo](){ toggle_complete(todo); });
            QHBoxLayout *l_row = new QHBoxLayout;
            l_row->addWidget(b_del_cur, 1);
            l_row->addWidget(b_edit_cur, 1);
            l_row->addWidget(b_toggle_cur, 1);
            QLabel *cur_lbl = new QLabel(QString::fromStdString(fmt_str));
            cur_lbl->setWordWrap(true);
            l_row->addWidget(cur_lbl, 100);

            // add to top or bottom layout, depending on whether todo is
            // complete or not
            if (todo.done) {
                l_done->addLayout(l_row);
            } else {
                l_todo->addLayout(l_row);
            }
        }
    // else override if there were no todos
    } else {
        l_todo->addWidget(new QLabel("<p>No to-dos found!</p>"));
    }
    l_main->addLayout(l_todo);
    l_main->addLayout(l_done);
    this->setLayout(l_main);
}

void GTodoListWidget::delete_todo(RecTodo todo) {
    QMessageBox *msgbox = new QMessageBox(this);
    msgbox->setWindowTitle("Delete to-do");
    msgbox->setText("Remove this to-do?");
    msgbox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgbox->setDefaultButton(QMessageBox::Ok);

    if (msgbox->exec() == QMessageBox::Ok) {
        db->delete_todo(todo.id);
        refresh();
    }
}

void GTodoListWidget::edit_todo(RecTodo todo) {
    GNewTodoDialog *editor = new GNewTodoDialog(this, todo);
    if (editor->exec() == QDialog::Accepted) {
        QString new_text;
        editor->get_details(&new_text);
        db->update_todo(todo.id, new_text.toUtf8().toStdString());
        refresh();
    }
}

void GTodoListWidget::toggle_complete(RecTodo todo) {
    log("ID: " + to_string(todo.id) + ", complete: " + to_string(todo.done));
    if (todo.done) {
        db->uncomplete_todo(todo.id);
    } else {
        db->complete_todo(todo.id);
    }
    refresh();
}
