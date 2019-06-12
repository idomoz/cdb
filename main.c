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
    dict *d = new_dict(10);
    set_item(d, "hio", (item_value) {STRING, {.string_value="nice"}});
    set_item(d, "hio2", (item_value) {INT, {.int_value=1234}});
    printf("%llu",get_item(d,"hio2").value.int_value);
    print_dict(d);
    return 0;

//    clock_t t;
//    double time_taken;
//    for (int i = 0; i< 10; i++) {
//        t = clock();
//        dict *my_dict = new_dict(8);
//        item_value rvalue;
//        char num[12];
//
//        for (int i = 0; i < 1000000; i++) {
//            sprintf(num, "%d", i);
//            rvalue = (item_value) {INT};
//            rvalue.value.int_value = i;
//            set_item(my_dict, num, rvalue);
//        }
//        for (int i = 10; i < 1000000; i++) {
//            sprintf(num, "%d", i);
//            delete_item(my_dict, num);
//        }
//        print_dict(my_dict);
//        delete_dict(my_dict);
//        t = clock() - t;
//        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
//        printf("%f\n", time_taken);
//    }
}