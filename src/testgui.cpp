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
    log_test("GUI00", "add valid appointment with description");
    log_test("GUI01", "add valid appointment without description");
    log_test("GUI04", "add appointment without title");
    // TODO: use ""appt'); drop table appointments;""
    log_test("GUI05", "appointment SQL injection attack");
    log_test("GUI10", "");

    // start GUI
    GuiHandler gui;
    char **fake_argv;
    gui.init(0, fake_argv);
}
