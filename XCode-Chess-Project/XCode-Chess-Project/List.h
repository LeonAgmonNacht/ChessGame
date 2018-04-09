//
//  ListImplemenation.h
//  XCode-Chess-Project
//
//  Created by Daniel Meltzer on 06/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef List_h
#define List_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DEFAULT_LIST_SIZE 64
#define COMPERATOR_FIRST_ITEM_SHOULD_BE_LATER 1
#define COMPERATOR_SECOND_ITEM_SHOULD_BE_LATER -1
#define COMPERATOR_BOTH_ITEMS_ARE_EQUAL 0

/**
 renaming a struct from .c file, allows to use the struct members privately
 */
typedef struct List List;


/**
 initialize list
 
 @param initialSize inital list size
 @param free_element free function to free each element upon deletion
 @return List with proper atributes
 */
List* init_list(size_t initialSize, void (*free_element)(void*),void* (*copy_element)(void*));


/**
 initlialie a list without the ability of copying it

 @param initialSize  inital list size
 @param free_element free function to free each element upon deletion
 @warning this list can't be copied!!!
 @return List with proper atributes
 */
List* init_list_without_copy(size_t initialSize, void (*free_element)(void*));


/**
 insert an item to the list
 
 @param list the list to insert an item to
 @param element the element to insert
 @return true - if the isnert succeded , false - if the array is fuel and couldn't exapnd it
 */
bool insert_item(List* list,void* element);


/**
 free a list's memory(and it's items)
 
 @param list the list to free
 */
void free_list(List* list);

/**
 get element from list with index
 
 @param list list to get elemnt from
 @param index index where eleement sits in list
 @return pointer to the element
 */
void* get_element(List* list, size_t index);


/**
 get last element in list
 
 @param list list to get elemnt from
 @return pointer to the element
 */
void* get_last_element(List* list);

/**
 delete an item
 @complexity O(n), n is number of items in list before deletion
 @param list list
 @param index index to delete item in
 @return true if everything is fine, false if list had to shrink and couldn't realloc
 */
bool delete_item(List* list,size_t index);


/**
 get items count
 
 @param list list to get items count for
 @return number of items
 */
size_t get_items_count(List* list);

/**
 deep copy using copy function
 
 @param list the list to copy
 @return new allocated list with same data
 */
List* copy_list(List* list);


/**
 sort the list in place. uses quick sort.
 @complexity O(nlog(n)),n = list->elementsCount
 @param list list
 @param compare compare function, should return 0 if items are equal, -1 if first should come before , 1 if second should come before(note: -1 and 1 are jsut standard, actually, any number would do, only the sign matters, but please don't break this convention)
 */
void sort_list(List* list,int (*compare)(const void *, const void*));
#endif /* ListImplemenation_h */

