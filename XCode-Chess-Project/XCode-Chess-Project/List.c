//
//  List.c
//  XCode-Chess-Project
//
//  Created by Daniel Meltzer on 06/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "List.h"
#include <string.h>
#define SHRINKING_AND_EXPANIDNG_CONSTANT 2
#define CONST_TO_SHRINK 4
#define LAST_INDEX_OF_LIST(list) list->arrayElementsCount-1
#define NUMBER_OF_BYTES_TO_COPY_AFTER_DELTED_INDEX(index) ((sizeof(void*))*(list->arrayElementsCount-index))
#define ADD_ONE(integer) (integer+1)
#define MAX(a,b) (a>b ? a:b)
#define MINIMUM_SIZE_OF_LIST 1
struct List{
    char** array;
    size_t arrayMaxSize;
    size_t arrayElementsCount;
    void (*free)(void*);
};


/**
 get items count
 
 @param list list to get items count for
 @return number of items
 */
size_t get_items_count(List* list){
    return list->arrayElementsCount;
}

/**
 initialize list
 
 @param initialSize initalSize, chosoe wisely
 @warning allocates memory, remeber to use 'freeList(List*)' to free
 
 @return List element, NULL IF MEMORY ALLOCATION FAILED
 */
List* init_list(size_t initialSize, void (*free)(void*)){
    List* newList = malloc(sizeof(List));
    if(newList!=NULL){
        newList->array = malloc(initialSize*sizeof(void*));
        if(newList->array!=NULL){
            newList->free = free;
            newList->arrayElementsCount = 0;
            newList->arrayMaxSize = initialSize;
            
        }
        else{
            free(newList);
            return NULL;
        }
    }
    return newList;
}

/**
 trying to expand list with one element, usually will
 
 @param list list to expand(it's array)
 @return true - expension succes, false - expension failed
 */
bool _expand_array_for_one_element(List* list){
    char** newArrayPointer = realloc(list->array, (ADD_ONE(list->arrayMaxSize))*sizeof(void*));
    if(newArrayPointer == NULL){
        return false;
    }
    else{
        list->array = newArrayPointer;
        list->arrayMaxSize = ADD_ONE(list->arrayMaxSize);
        return true;
    }
}

/**
 trying to expand list
 
 @param list list to expand(it's array)
 @return true - expension succes, false - expension failed
 */
bool _expand_list(List* list){
    
    char** newArrayPointer = realloc((list->array), list->arrayMaxSize*sizeof(void*)*SHRINKING_AND_EXPANIDNG_CONSTANT);
    
    if(newArrayPointer == NULL){
        if(!_expand_array_for_one_element(list)){
            return false;
        }
    }
    else{
        list->array = newArrayPointer;
        list->arrayMaxSize = list->arrayMaxSize*SHRINKING_AND_EXPANIDNG_CONSTANT;
    }
    
    return true;
}


/**
 insert an item to the list
 
 @param list the list to insert an item to
 @param element the element to insert
 @complexity O(1) - amortized , worstcase - O(n)
 @return true - if the insert succeded , false - if the array is fuel and couldn't exapnd it
 */
bool insert_item(List* list,void* element){
    if(list->arrayElementsCount == list->arrayMaxSize){
        
        if(!_expand_list(list)){
            return false;
        }
        
        
    }
    
    // calcuate index to insert and then increae elements count
    
    //copy item to array
    char** helper = (char**)&(element);
    memcpy(list->array+list->arrayElementsCount++, helper, sizeof(void*));
    
    
    
    return true;
}


/**
 delete an item
 @complexity O(n-index), n is number of items in list before deletion
 @param list list
 @param index index to delete item in
 @return true if everything is fine, false if list had to shrink and couldn't realloc
 */
bool delete_item(List* list,size_t index){
    if(list->arrayElementsCount>index){
        list->arrayElementsCount = list->arrayElementsCount-1;
        if(index < LAST_INDEX_OF_LIST(list)){
            char** itemToDelete = list->array + index;
            char** nextItem = list->array + ADD_ONE(index);
            
            memcpy(itemToDelete, nextItem, NUMBER_OF_BYTES_TO_COPY_AFTER_DELTED_INDEX(index));
        }
        if(get_items_count(list)<list->arrayMaxSize/CONST_TO_SHRINK){
            size_t newSize = SHRINKING_AND_EXPANIDNG_CONSTANT*list->arrayElementsCount;
            if(MAX(newSize,MINIMUM_SIZE_OF_LIST)!= MINIMUM_SIZE_OF_LIST){
                char** newArr = realloc(list->array,newSize*sizeof(void*));
                if(newArr == NULL){
                    return false;
                }
                else{
                    list->array = newArr;
                }
            }
        }
        
    }
    return true;
}



/**
 get element from list with index
 
 @param list list to get elemnt from
 @param index index where eleement sits in list
 @return pointer to the element
 */
void* get_element(List* list, size_t index){
    char** pointerTopointerinList = (list->array + index);
    char* element = *pointerTopointerinList;
    return element;
}



/**
 get last element in list
 
 @param list list to get elemnt from
 @return pointer to the element
 */
void* get_last_element(List* list){
    return get_element(list, LAST_INDEX_OF_LIST(list));
}
/**
 free a list's memory(and it's items)
 
 @param list the list to free
 */
void free_list(List* list){
    for(int i =0;i<get_items_count(list);i++){
        list->free(get_element(list, i));
    }
    free(list->array);
    free(list);
}

/**
 shallow copy,copies the list as is
 
 @param list the list to copy
 @return new allocated list with same data
 */
List* copy_list(List* list){
    List* newList = malloc(sizeof(List));
    if(newList == NULL){
        return NULL;
    }
    newList->arrayElementsCount = list->arrayElementsCount;
    newList->arrayMaxSize = list->arrayMaxSize;
    newList->array = malloc(sizeof(void*)*(list->arrayMaxSize));
    if(newList->array == NULL){
        free_list(newList);
        return NULL;
    }
    memcpy(newList->array, list->array, sizeof(sizeof(void*)*list->arrayElementsCount));
    return newList;
}
/**
 sort the list in place. uses quick sort.
 @complexity O(nlog(n)),n = list->elementsCount
 @param list list
 @param compare compare function, should return 0 if items are equal, 1 if first should come before , -1 if second should come before(note: -1 and 1 are jsut standard, actually, any number would do, only the sign matters, but please don't break this convention)
 @warning comparator recives pointer to pointer!!!
 */
void sort_list(List* list,int (*compare)(const void *, const void*))
{
    qsort(list->array,list->arrayElementsCount,sizeof(void*),compare);
}

