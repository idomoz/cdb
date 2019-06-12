//
// Created by Ido Mozes on 09/06/2019.
//

#ifndef CDB_DICT_H
#define CDB_DICT_H

#include <stdio.h>
#include <stdint.h>
#include "bucket.h"
#include "cdb_types.h"

dict *new_dict(uint64_t initial_size);

void set_item(dict *dict, char *key_value, item_value item_value);

item_value get_item(dict *dict, char *key_value);

int delete_item(dict *dict, char *key_value);

void delete_dict(dict *dict);

dict_iterator iter_dict(dict *dict);

char *next_key(dict_iterator *iterator);

item_value next_value(dict_iterator *iterator);

item next_item(dict_iterator *iterator);
void print_dict(dict * dict);

#endif //CDB_DICT_H
