//
// Created by Ido Mozes on 09/06/2019.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include "bucket.h"


_bucket _new_bucket() {
    return (_bucket) {0, NULL};
}

int _append_node(_bucket *bucket, _item_node *node) {
    if (bucket->length == UINT64_MAX)
        return 0;
    if (bucket->length == 0) {
        bucket->first_node = node;
        node->next = NULL;
    } else {
        node->next = bucket->first_node;
        bucket->first_node = node;
    }
    bucket->length++;
    return 1;
}

item_value  _get_item_from_bucket(_bucket *bucket, _key *key) {
    for (_item_node *node = bucket->first_node; node != NULL; node = node->next) {
        if (_compare_keys(key, &node->key))
            return node->item_value;
    }
    return (item_value){NOT_FOUND,0};
}

int _delete_item_from_bucket(_bucket *bucket, _key *key) {
    for (_item_node *node = bucket->first_node, *prev_node = NULL; node != NULL; prev_node = node, node = node->next) {
        if (_compare_keys(key, &node->key)) {
            bucket->length--;
            if (prev_node == NULL)
                bucket->first_node = node->next;
            else
                prev_node->next = node->next;
            _delete_item_node(node);
            return 1;
        }
    }
    return 0;
}

void _delete_bucket(_bucket *bucket) {
    for (_item_node *node = bucket->first_node, *next_node = NULL; node != NULL; node = next_node) {
        next_node = node->next;
        _delete_item_node(node);
    }
}
