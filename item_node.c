//
// Created by Ido Mozes on 09/06/2019.
//
#include <string.h>
#include <malloc.h>
#include "item_node.h"

char *clone(char *str_p) {
    return strcpy((char *) malloc(strlen((str_p)) + 1), (str_p));
}

_item_node *_new_item(_key *key, item_value value) {
    _item_node *new_item_node = (_item_node *) malloc(sizeof(_item_node));
    *new_item_node = (_item_node) {*key, value, NULL};
    return new_item_node;
}

void delete_item_value(item_value *item_value) {
    switch (item_value->type) {
        case STRING:
            free(item_value->value.string_value);
            break;
        case DICT:
            delete_dict(item_value->value.dict_value);
            break;
        case ARRAY:
            delete_array(item_value->value.array_value);
            break;
        default:
            break;
    }
}

void _delete_item_node(_item_node *item) {
    free(item->key.value);
    delete_item_value(&item->item_value);
    free(item);
}

void delete_return_item(item *r_item) {
    free(r_item->key);
    delete_item_value(&r_item->item_value);
}

int _compare_keys(_key *key1, _key *key2) {
    return (key1->hash[0] == key2->hash[0]) && (key1->hash[1] == key2->hash[1]) &&
           (strcmp(key1->value, key2->value) == 0);
}

