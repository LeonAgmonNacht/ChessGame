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
#include <string.h>
int tests_run = 0;
List* l;
typedef struct structa{
    int a[1000];
}Str;
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
void* copy_item(void* item){
    int* a = malloc(sizeof(int));
    *a = *(int*)item;
    return a;
    
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
static char* next_insert_test_after_deletion(){
    for(int i = 0;i<20;i++){
        int* j =malloc(sizeof(int));
        *j = i;
        insert_item(l, j);
    }
    mu_assert("failed insert", get_items_count(l)>=20);
    return 0;
}
static char* free_test(){
    free_list(l);
    l = init_list(1, free, copy_item);
    int const limit = 20000000;
    for(int i = 0;i<limit;i++){
        int* j =malloc(sizeof(int));
        *j = i;
        insert_item(l, j);
    }
    for(int i = 0;i<limit;i++){
        int* j = get_element(l, i);
        mu_assert("error,insert failed", (*j) == i);
    }
    free_list(l);
    return 0;
}
static char* copy_check(){
    l = init_list(1, free,copy_item);
    for(int i = 0;i<20000;i++){
        int* j =malloc(sizeof(int));
        *j = i;
        insert_item(l, j);
    }
    List* c[10000];
    for(int i = 0;i<10000;i++){
        c[i] = copy_list(l);
    }
    free_list(l);
    for(int i =0;i<9999;i++){
        free_list(c[i]);
    }
    for(int i = 0;i<20000;i++){
        int* j = get_element(c[9999], i);
        mu_assert("copy fail", *j == i);
    }
    free_list(c[9999]);
    
    return 0;
}
int compareOne(const void* a, const void* j){
     int** first = (int**)a;
     int** second = (int**)j;
    return (**first > **second) ? (-1):(**first == **second ? 0:1);
}
static char* sort_check(){
    l = init_list(1, free, copy_item);
    int const limit = 100000000;
    for(int i = 0;i<limit;i++){
        int* j =malloc(sizeof(int));
        *j = i;
        insert_item(l, j);
    }
    sort_list(l, compareOne);
    for(int i = 0; i<limit;i++){
        int* num = get_element(l, i);
        mu_assert("error in sorting", *num == (limit - 1 - i));
    }
    free_list(l);
    return 0;
}
void* copy_struct(void* str){
    Str* s = malloc(sizeof(Str));
    memcpy(s, str, sizeof(Str));
    return s;
}
static char* check_struct(){
    l =init_list(1, free, copy_item);
    int const limit = 1000000;
    for(int i = 0;i<limit;i++){
        Str* new = malloc(sizeof(Str));
        for(int j = 0;j<1000;j++){
            new->a[j]=i;
        }
        insert_item(l, new);
    }
    delete_item(l, 0);
    for(int i = 1;i<limit;i++){
        int realI = i-1;
        Str* old = get_element(l, realI);
        for(int j = 0;j<1000;j++){
            mu_assert("struct error",old->a[j]  == i);
        }
    }
    free_list(l);
    return 0;
}
static char * all_tests() {
    l= init_list(1, free,copy_item);
    mu_run_test(insert_test);
    mu_run_test(delete_test);
    mu_run_test(next_insert_test_after_deletion);
    mu_run_test(free_test);
    mu_run_test(copy_check);
    mu_run_test(sort_check);
    mu_run_test(check_struct);
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
