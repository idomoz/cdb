//
// Created by Ido Mozes on 10/06/2019.
//

#ifndef CDB_ARRAY_H
#define CDB_ARRAY_H

#include "cdb_types.h"


array *new_array(value_type type, uint64_t length);

void delete_array(array *_array);

#endif //CDB_ARRAY_H
