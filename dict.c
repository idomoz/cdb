//
// Created by Ido Mozes on 09/06/2019.
//
#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>
#include "dict.h"
#include "murmur3.h"

dict *new_dict(uint64_t initial_size) {
    dict *new_dict = (dict *) malloc(sizeof(dict));
    *new_dict = (dict) {(_bucket *) malloc(sizeof(_bucket) * initial_size), initial_size, 0};
    for (int i = 0; i < initial_size; i++)
        new_dict->buckets[i] = _new_bucket();
    return new_dict;
}

static uint64_t _calc_location(_key *key, uint64_t n_buckets) {
    return (key->hash[0] + key->hash[1]) % n_buckets;
}

static void _resize(dict *dict) {
    if (dict->n_buckets == UINT64_MAX)
        return;
    uint64_t new_n_buckets = dict->n_buckets * 2;
    if (dict->n_buckets > new_n_buckets)
        new_n_buckets = UINT64_MAX;

    _bucket *new_buckets = (_bucket *) malloc(sizeof(_bucket) * new_n_buckets);
    for (int i = 0; i < new_n_buckets; i++)
        new_buckets[i] = _new_bucket();

    for (int i_bucket = 0; i_bucket < dict->n_buckets; i_bucket++) {
        for (_item_node *node = dict->buckets[i_bucket].first_node, *next_node = NULL; node != NULL; node = next_node) {
            next_node = node->next;
            _append_node(new_buckets + _calc_location(&node->key, new_n_buckets), node);
        }
    }
    free(dict->buckets);
    dict->buckets = new_buckets;
    dict->n_buckets = new_n_buckets;
}

static _key _create_key(char *key_value) {
    _key new_key = (_key) {{0}, clone(key_value)};
    MurmurHash3_x64_128(key_value, strlen(key_value), 42, new_key.hash);
    return new_key;
}

int add_item(dict *dict, char *key_value, item_value item_value) {
    if (item_value.type == NOT_FOUND || dict->n_items == UINT64_MAX || key_value == NULL)
        return 0;
    if (dict->n_items >= dict->n_buckets * 0.75)
        _resize(dict);
    _key key = _create_key(key_value);
    if (item_value.type == STRING)
        item_value.value.string_value = clone(item_value.value.string_value);
    if (_append_node(dict->buckets + _calc_location(&key, dict->n_buckets), _new_item(&key, item_value))) {
        dict->n_items++;
        return 1;
    }
    return 0;
}

item_value get_item(dict *dict, char *key_value) {
    if (key_value == NULL)
        return (item_value) {NOT_FOUND};
    _key key = _create_key(key_value);
    item_value item_value = _get_item_from_bucket(dict->buckets + _calc_location(&key, dict->n_buckets), &key);
    free(key.value);
    if (item_value.type == STRING)
        item_value.value.string_value = clone(item_value.value.string_value);
    return item_value;
}

int delete_item(dict *dict, char *key_value) {
    if (key_value == NULL)
        return 0;
    _key key = _create_key(key_value);
    if (_delete_item_from_bucket(dict->buckets + _calc_location(&key, dict->n_buckets), &key)) {
        dict->n_items--;
        return 1;
    }
    return 0;
}

void delete_dict(dict *dict) {
    for (int i = 0; i < dict->n_buckets; i++)
        _delete_bucket(dict->buckets + i);
    free(dict->buckets);
    free(dict);
}

dict_iterator iter_dict(dict *dict) {
    return (dict_iterator) {dict, 0, NULL};
}

static _item_node *_next_node(dict_iterator *iterator) {
    if (iterator->i_bucket == iterator->dict->n_buckets) {
        return NULL;
    }
    if (iterator->node == NULL)
        iterator->node = iterator->dict->buckets[0].first_node;
    else
        iterator->node = iterator->node->next;

    while (iterator->node == NULL && ++iterator->i_bucket < iterator->dict->n_buckets) {
        iterator->node = iterator->dict->buckets[iterator->i_bucket].first_node;
    }
    return iterator->node;
}

char *next_key(dict_iterator *iterator) {
    _item_node *next_node = _next_node(iterator);
    return next_node != NULL ? clone(next_node->key.value) : NULL;
}

item_value next_value(dict_iterator *iterator) {
    _item_node *next_node = _next_node(iterator);
    if (next_node != NULL) {
        item_value next_value = next_node->item_value;
        if (next_value.type == STRING)
            next_value.value.string_value = clone(next_value.value.string_value);
        return next_value;
    }
    return (item_value) {NOT_FOUND};
}

item next_item(dict_iterator *iterator) {
    _item_node *next_node = _next_node(iterator);
    if (next_node != NULL) {
        item next_item = (item) {clone(next_node->key.value), next_node->item_value};
        if (next_item.item_value.type == STRING)
            next_item.item_value.value.string_value = clone(next_item.item_value.value.string_value);
        return next_item;
    }
    return (item) {NULL};
}
