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
    int sizeOfElement;
    void (*free)(void*);
};

/**
 get bytes offest from index
 
 @param index index of element in array
 @return number of bytes from the begining of the array where the index represents
 */
size_t _get_bytes_offest_from_index(size_t index){
    return index*sizeof(void*);
}
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
 @warning the list copies data, if you want to use pointers the element should be pointers and you should insert with pointers to pointers
 @return List element, NULL IF MEMORY ALLOCATION FAILED
 */
List* init_list(size_t initialSize, int sizeOfElement, void (*free)(void*)){
    List* newList = malloc(sizeof(List));
    if(newList!=NULL){
        newList->array = malloc(initialSize*sizeof(void*));
        if(newList->array!=NULL){
            newList->free = free;
            newList->arrayElementsCount = 0;
            newList->arrayMaxSize = initialSize;
            newList->sizeOfElement = sizeOfElement;
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
    char** newArrayPointer = realloc(list->array, list->arrayMaxSize*sizeof(void*)*SHRINKING_AND_EXPANIDNG_CONSTANT);
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
 @warning copies the element
 @return true - if the insert succeded , false - if the array is fuel and couldn't exapnd it
 */
bool insert_item(List* list,void* element){
    if(list->arrayElementsCount == list->arrayMaxSize){
        
        if(!_expand_list(list)){
            return false;
        }
        
        
    }
    
    // calcuate index to insert and then increae elements count
    size_t index = _get_bytes_offest_from_index(list->arrayElementsCount++);
    //copy item to array
    memcpy(list->array+index, &element, sizeof(void*));
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
            char** itemToDelete = list->array + _get_bytes_offest_from_index(index);
            char** nextItem = list->array + _get_bytes_offest_from_index(ADD_ONE(index));
            
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
 get element using pointer to list element

 @param list list
 @param ptrToListElement pointer to list element
 @return index of element in list
 */
size_t get_element_index_using_pointer_to_list_element(List* list,void* ptrToListElement){
    size_t index = ((char**)ptrToListElement - list->array)/list->sizeOfElement;
    return index;
}


/**
 get element from list with index
 
 @param list list to get elemnt from
 @param index index where eleement sits in list
 @return pointer to the element
 */
void* get_element(List* list, size_t index){
    size_t bytesOffeset= _get_bytes_offest_from_index(index);
    char** pointerTopointerinList = (list->array + bytesOffeset);
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
