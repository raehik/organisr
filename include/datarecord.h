#ifndef DATARECORD_H
#define DATARECORD_H

#include <vector>
#include "dataobject.h"


class DataRecord
{
public:
    // Doesn't (yet) keep info on 'columns' (we go by order).
    DataRecord();
    DataObject get_object(int index);
    void add(DataObject obj);
    int size();

private:
    std::vector<DataObject> record;
};

#endif // DATARECORD_H
