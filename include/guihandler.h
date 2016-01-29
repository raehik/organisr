#ifndef GUIHANDLER_H
#define GUIHANDLER_H

/**
 * \brief A barebones wrapper for starting the Qt GUI.
 *
 * Has to be separate from layouts & widgets etc. because otherwise Qt would
 * complain about a QWidget being created earlier than the QApplication.
 */
class GuiHandler
{
public:
    GuiHandler();

    /**
     * \brief Initialise the GUI.
     *
     * We do this before connecting to the database so that we can display errors
     * using the GUI.
     */
    int init(int argc, char *argv[]);
};

#endif // GUIHANDLER_H
