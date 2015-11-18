#ifndef DIALOGADDTODO_H
#define DIALOGADDTODO_H

#include <QDialog>

namespace Ui {
class DialogAddTodo;
}

class DialogAddTodo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTodo(QWidget *parent = 0);
    ~DialogAddTodo();

private:
    Ui::DialogAddTodo *ui;
};

#endif // DIALOGADDTODO_H
