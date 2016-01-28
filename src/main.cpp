#include "guihandler.h"
#include <iostream>
#include "testcommon.h"
#include "testsql.h"
#include "testgui.h"

int main(int argc, char *argv[]) {
    //GuiHandler gui;
    //return gui.init(argc, argv);
    Test::init_tests();
    test_sql();
    test_gui();
}
