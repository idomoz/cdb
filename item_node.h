//
// Created by Ido Mozes on 09/06/2019.
//

#ifndef CDB_ITEM_NODE_H
#define CDB_ITEM_NODE_H

#include <stdint.h>
#include "bucket.h"
#include "dict.h"
#include "array.h"
#include "cdb_types.h"

char *clone(char *str_p);

_item_node *_new_item(_key *key, item_value * value);

void delete_item_value(item_value *item_value);

void _delete_item_node(_item_node *item);

void delete_return_item(item *r_item);

void print_item_value(item_value *item_value);

#endif //CDB_ITEM_NODE_H
