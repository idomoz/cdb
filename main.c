//
// Created by Ido Mozes on 09/06/2019.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <time.h>
#include "dict.h"

int main() {
    dict *my_dict = new_dict(8);
    item_value rvalue;
    item r_item;
    char *hello = "hello";
    char num[9];

    for (int i = 0; i < 1000; i++) {
        sprintf(num, "%d", i);
        strcat(num, hello);
        rvalue = (item_value) {INT};
        rvalue.value.int_value = i;
        add_item(my_dict, num, rvalue);
    }
    dict_iterator it = iter_dict(my_dict);
    while((r_item = next_item(&it)).key != NULL) {
        printf("\"%s\": %llu\n", r_item.key, r_item.item_value.value.int_value);
        delete_return_item(&r_item);
    }
    delete_dict(my_dict);

}