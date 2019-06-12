//
// Created by Ido Mozes on 10/06/2019.
//
#include <malloc.h>
#include "dict.h"
#include "array.h"

array *new_array(value_type type, uint64_t length) {
    if (type == NONE || type == NOT_FOUND)
        return NULL;
    array *new_array = (array *) malloc(sizeof(array));
    *new_array = (array) {type, length, NULL};
    int item_size;
    switch (type) {
        case INT:
            item_size = sizeof(uint64_t);
            break;
        case DOUBLE:
            item_size = sizeof(double);
            break;
        case BOOL:
            item_size = 1;
            break;
        default:
            item_size = sizeof(void *);
    }
    new_array->values = malloc(item_size * length);
    return new_array;
}

void delete_array(array *_array) {
    if (_array->type >= STRING)
        for (int i = 0; i < _array->length; i++) {
            switch (_array->type) {
                case STRING:
                    free((void *) (_array->values)[i]);
                    break;
                case DICT:
                    delete_dict((dict *) (_array->values)[i]);
                    break;
                case ARRAY:
                    delete_array((array *) (_array->values)[i]);
                    break;
                default:
                    break;
            }
        }
    free(_array->values);
    free(_array);
}