#include "dialogaddtodo.h"
#include "ui_dialogaddtodo.h"

DialogAddTodo::DialogAddTodo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddTodo)
{
    ui->setupUi(this);
}

DialogAddTodo::~DialogAddTodo()
{
    delete ui;
}
