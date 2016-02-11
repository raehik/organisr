#include "datarecord.h"

#include "log.h"

using namespace Util;

DataRecord::DataRecord() {
}

DataObject DataRecord::get_object(int index) {
    if (index > size() - 1) {
        error("get_object(): index is out of range");
        error("TODO throw sth.");
    }
    return record[index];
}

void DataRecord::add(DataObject obj) {
    record.push_back(obj);
}

int DataRecord::size() {
    return record.size();
}
