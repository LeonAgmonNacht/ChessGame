//
//  ListTesting.c
//  test
//
//  Created by Daniel Meltzer on 28/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ListTesting.h"
#include "minunit.h"
#include "List.h"

int tests_run = 0;
List* l;
static char * insert_test(){
    
    for(int i = 0;i<20;i++){
        int* j =malloc(sizeof(int));
        *j = i;
        insert_item(l, j);
    }
    for(int i = 0;i<20;i++){
        int* j = get_element(l, i);
        mu_assert("error,insert failed", (*j) == i);
    }
    return 0;
}
static char* delete_test(){
    
    delete_item(l, 5);
    delete_item(l, 3);
    mu_assert("delte item cound fialed", get_items_count(l) == 18 );
    for(int i = 0;i<get_items_count(l);i++){
        mu_assert("delete failed", *(int*)get_element(l, i) != 3);
        mu_assert("delete failed", *(int*)get_element(l, i) != 5);
    }
    for(int i =0;i<15;i++){
        delete_item(l, 0);
    }
    mu_assert("get failed 17", *(int*)get_element(l, 0) == 17 );
    mu_assert("18", *(int*)get_element(l, 1) == 18);
    mu_assert("19", *(int*)get_element(l, 2) == 19);
    return 0;
}
static char* free_test(){
    free_list(l);
    return 0;
}
static char * all_tests() {
    l= init_list(1, free);
    mu_run_test(insert_test);
    mu_run_test(delete_test);
    mu_run_test(free_test);
    return 0;
}
void test(){
     char *result =all_tests();
   
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
}
