#ifndef GUIHANDLER_H
#define GUIHANDLER_H

/**
 * @brief A barebones wrapper for starting the Qt GUI.
 *
 * Has to be separate from layouts & widgets etc. because otherwise Qt would
 * complain about a QWidget being created earlier than the QApplication.
 */
class GuiHandler {
    public:
        GuiHandler();
        int init(int argc, char *argv[]);
};

#endif // GUIHANDLER_H
