#include "todorow.h"
#include "datahandler.h"
#include "log.h"

using namespace Util;

TodoRow::TodoRow(std::string text, int id, int done) {
    this->text = text;
    this->id = id;
    if (done == DataHandler::TODO_UNFIN) {
        this->done = false;
    } else if (done == DataHandler::TODO_FIN) {
        this->done = true;
    } else {
        error("TodoRow: 'done' was not TODO_FIN or TODO_UNFIN, defaulting to TODO_UNFIN");
        this->done = false;
    }
}

std::string TodoRow::get_text() {
    return text;
}

int TodoRow::get_id() {
    return id;
}

bool TodoRow::get_done() {
    return done;
}
