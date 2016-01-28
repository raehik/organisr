#include "testgui.h"
#include <stdio.h>
#include "dbobject.h"
#include <fstream>
#include "sqlitehelper.h"
#include "guihandler.h"

using namespace Test;

int init_gui_tests() {
    return 0;
}

void test_gui() {
    init_gui_tests();
    log_test("GUI00", "open ");
    GuiHandler gui;
    char **fake_argv;
    gui.init(0, fake_argv);
}
