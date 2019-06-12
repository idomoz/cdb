//
// Created by Ido Mozes on 09/06/2019.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include "bucket.h"


void _set_item(_item_node **first_node, _key *key, item_value *value) {
    _item_node *current_node = _get_node(*first_node, key);
    if (current_node != NULL)
        current_node->item_value = *value;
    else
        _append_node(first_node, _new_item(key, value));
}

void _append_node(_item_node **first_node, _item_node *node) {
    if (*first_node == NULL) {
        *first_node = node;
        node->next = NULL;
    } else {
        node->next = *first_node;
        *first_node = node;
    }
}

_item_node *_get_node(_item_node *node, _key *key) {
    for (; node != NULL; node = node->next) {
        if (key->hash == node->key.hash && strcmp(key->value, node->key.value) == 0)
            return node;
    }
    return NULL;
}

int _delete_item_from_bucket(_item_node **first_node, _key *key) {
    for (_item_node *node = *first_node, *prev_node = NULL; node != NULL; prev_node = node, node = node->next) {
        if (key->hash == node->key.hash && strcmp(key->value, node->key.value) == 0) {
            if (prev_node == NULL)
                *first_node = node->next;
            else
                prev_node->next = node->next;
            _delete_item_node(node);
            return 1;
        }
    }
    return 0;
}

void _delete_bucket(_item_node *node) {
    for (_item_node *next_node = NULL; node != NULL; node = next_node) {
        next_node = node->next;
        _delete_item_node(node);
    }
}
