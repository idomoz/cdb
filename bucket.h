//
// Created by Ido Mozes on 09/06/2019.
//

#ifndef CDB_BUCKET_H
#define CDB_BUCKET_H

#include <stdio.h>
#include "item_node.h"
#include "cdb_types.h"


_bucket _new_bucket();

int _append_node(_bucket *bucket, _item_node *node);

item_value _get_item_from_bucket(_bucket *bucket, _key *key);

int _delete_item_from_bucket(_bucket *bucket, _key *key);

void _delete_bucket(_bucket *bucket);

#endif //CDB_BUCKET_H
