#ifndef WARNINGBOX_H
#define WARNINGBOX_H

#include <QMessageBox>
#include <QString>

/**
 * @brief A message box for user warnings.
 *
 * This is a convenience class to make it easy to bring up a warning dialog box.
 * Most often, you should instantiate an object of this class like so:
 *
 *     WarningBox("You did something bad");
 *
 * Using this syntax, it should be deleted when the user closes the dialog
 * (rather than using `new` and having to `delete` it manually).
 */
class WarningBox : public QMessageBox
{

    Q_OBJECT

public:
    WarningBox(QString text, QWidget *parent = 0);
    virtual ~WarningBox();

private:
    void init_window();
};

#endif // WARNINGBOX_H
