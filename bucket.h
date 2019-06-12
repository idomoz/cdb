//
// Created by Ido Mozes on 09/06/2019.
//

#ifndef CDB_BUCKET_H
#define CDB_BUCKET_H

#include <stdio.h>
#include "item_node.h"
#include "cdb_types.h"


void _set_item(_item_node **first_node,_key * key, item_value * value);

void _append_node(_item_node **first_node, _item_node *node);

_item_node * _get_node(_item_node *node, _key *key);

int _delete_item_from_bucket(_item_node **first_node, _key *key);

void _delete_bucket(_item_node *node);

#endif //CDB_BUCKET_H
