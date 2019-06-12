//
// Created by Ido Mozes on 11/06/2019.
//

#ifndef CDB_CDB_TYPES_H
#define CDB_CDB_TYPES_H

#include <stdint.h>

struct _array;
struct _dict;
enum _value_type {
    INT,
    UINT,
    DOUBLE,
    BOOL,
    STRING,
    DICT,
    ARRAY,
    NONE,
    NOT_FOUND
};
union _value;
struct _item_value;
struct __key;
struct __item_node;
struct _item;
struct _dict_iterator;

typedef struct _array array;
typedef struct _dict dict;
typedef enum _value_type value_type;
typedef union _value value;
typedef struct _item_value item_value;
typedef struct __key _key;
typedef struct __item_node _item_node;
typedef struct _item item;
typedef struct _dict_iterator dict_iterator;

struct _array {
    value_type type;
    uint64_t length;
    void **values;
};


struct _dict {
    _item_node ** buckets;
    uint64_t n_buckets;
    uint64_t n_items;
};

union _value {
    int64_t int_value;
    uint64_t uint_value;
    double double_value;
    char bool_value;
    char *string_value;
    dict *dict_value;
    array *array_value;
};

struct _item_value {
    value_type type;
    value value;
};

struct __key {
    uint64_t hash;
    char *value;
};

struct __item_node {
    _key key;
    item_value item_value;
    _item_node *next;
};

struct _item {
    char *key;
    item_value item_value;
};

struct _dict_iterator {
    dict * dict;
    uint64_t i_bucket;
    _item_node * node;
};
#endif //CDB_CDB_TYPES_H
