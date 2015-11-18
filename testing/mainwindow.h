#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QObject>


class MainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void newWindow(std::string win_name);
};

#endif // MAINWINDOW_H
