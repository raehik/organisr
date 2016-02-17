#include "gtodolistwidget.h"
#include "gmainwindow.h"
#include "todorow.h"
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
    std::vector<TodoRow> todos = db->get_todos();

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
        for (std::vector<TodoRow>::size_type i = 0; i != todos.size(); i++) {
            std::string t_text = todos[i].get_text();
            int t_id = todos[i].get_id();
            bool t_done = todos[i].get_done();

            // get & format to-do (HTML escape for safety)
            std::string cur_todo = "<p style='font-size: 10pt'>&bull; ";
            if (t_done) { cur_todo += "<s>"; }
            std::string todo_formatted = QString::fromStdString(
                        t_text).toHtmlEscaped().toUtf8().toStdString();
            cur_todo += todo_formatted + "</p>";
            if (t_done) { cur_todo += "</s>"; }

            // add delete/edit buttons
            QPushButton *b_del_cur = new QPushButton("X");
            QPushButton *b_edit_cur = new QPushButton("E");
            QPushButton *b_toggle_cur = new QPushButton("✓");

            b_del_cur->setMinimumWidth(20);
            b_edit_cur->setMinimumWidth(20);
            b_toggle_cur->setMinimumWidth(20);

            connect(b_del_cur, &QPushButton::clicked, this, [this, t_id](){ delete_todo(t_id); });
            connect(b_edit_cur, &QPushButton::clicked, this, [this, t_id, t_text](){ edit_todo(t_id, t_text); });
            connect(b_toggle_cur, &QPushButton::clicked, this, [this, t_id, t_done](){ toggle_complete(t_id, t_done); });
            QHBoxLayout *l_row = new QHBoxLayout;
            l_row->addWidget(b_del_cur, 1);
            l_row->addWidget(b_edit_cur, 1);
            l_row->addWidget(b_toggle_cur, 1);
            QLabel *cur_lbl = new QLabel(QString::fromStdString(cur_todo));
            cur_lbl->setWordWrap(true);
            l_row->addWidget(cur_lbl, 100);

            // add to top or bottom layout, depending on whether todo is
            // complete or not
            if (t_done) {
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

void GTodoListWidget::delete_todo(int id) {
    QMessageBox *msgbox = new QMessageBox(this);
    msgbox->setWindowTitle("Delete to-do");
    msgbox->setText("Remove this to-do?");
    msgbox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgbox->setDefaultButton(QMessageBox::Ok);

    if (msgbox->exec() == QMessageBox::Ok) {
        db->delete_todo(id);
        refresh();
    }
}

void GTodoListWidget::edit_todo(int id, std::string cur_text) {
    GNewTodoDialog *editor = new GNewTodoDialog(this, cur_text);
    if (editor->exec() == QDialog::Accepted) {
        QString todo_text;
        editor->get_details(&todo_text);
        db->update_todo(id, todo_text.toUtf8().toStdString());
        refresh();
    }
}

void GTodoListWidget::toggle_complete(int id, bool complete) {
    log("ID: " + to_string(id) + ", complete: " + to_string(complete));
    if (complete) {
        db->uncomplete_todo(id);
    } else {
        db->complete_todo(id);
    }
    refresh();
}
