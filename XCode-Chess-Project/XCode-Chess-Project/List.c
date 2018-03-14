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
#define LAST_INDEX_OF_LIST(list) list->arrayElementsCount-1
struct List{
    char* array;
    size_t arrayMaxSize;
    size_t arrayElementsCount;
    int sizeOfElement;
};

/**
 get bytes offest from index
 
 @param index index of element in array
 @param sizeOfElement size of element
 @return number of bytes from the begining of the array where the index represents
 */
size_t _get_bytes_offest_from_index(size_t index,size_t sizeOfElement){
    return index*sizeOfElement;
}


/**
 initialize list
 
 @param initialSize initalSize, chosoe wisely
 @param sizeOfElement sizeOfElement
 @warning allocates memory, remeber to use 'freeList(List*)' to free
 @warning the list copies data, if you want to use pointers the element should be pointers and you should insert with pointers to pointers
 @return List element
 */
List* init_list(size_t initialSize, int sizeOfElement){
    List* newList = malloc(sizeof(List));
    if(newList!=NULL){
        newList->array = malloc(initialSize*sizeOfElement);
        if(newList->array!=NULL){
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
    char* newArrayPointer = realloc(list->array, list->arrayMaxSize+1);
    if(newArrayPointer == NULL){
        return false;
    }
    else{
        list->array = newArrayPointer;
        list->arrayMaxSize = list->arrayMaxSize+1;
        return true;
    }
}

/**
 trying to expand list
 
 @param list list to expand(it's array)
 @return true - expension succes, false - expension failed
 */
bool _expand_list(List* list){
    char* newArrayPointer = realloc(list->array, list->arrayMaxSize*SHRINKING_AND_EXPANIDNG_CONSTANT);
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
    size_t index = _get_bytes_offest_from_index(list->arrayElementsCount++, list->sizeOfElement);
    //copy item to array
    memcpy(list->array+index, &element, list->sizeOfElement);
    return true;
}


/**
 delete an item
 @complexity O(n), n is number of items in list before deletion
 @param list list
 @param index index to delete item in
 @return true if everything is fine, false if list had to shrink and couldn't realloc
 */
bool delete_item(List* list,size_t index){
    if(list->arrayElementsCount>index){
        size_t indexInBytes = _get_bytes_offest_from_index(list->arrayElementsCount++, list->sizeOfElement);
        for(size_t i = index+1;i<list->arrayElementsCount;i++){
            memcpy(list->array+indexInBytes, list->array+indexInBytes+1, list->sizeOfElement);
        }
        list->arrayElementsCount = LAST_INDEX_OF_LIST(list);
        if(list->arrayElementsCount < list->arrayMaxSize/SHRINKING_AND_EXPANIDNG_CONSTANT){
            char* newArrayPointer = realloc(list->array, list->arrayMaxSize/SHRINKING_AND_EXPANIDNG_CONSTANT);
            if(newArrayPointer!=NULL){
                list->array = newArrayPointer;
                list->arrayMaxSize = list->arrayMaxSize/SHRINKING_AND_EXPANIDNG_CONSTANT;
            }
            else{
                return false;
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
    size_t bytesOffeset= _get_bytes_offest_from_index(index, list->sizeOfElement);
    return list->array+bytesOffeset;
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
 get last element in list
 
 @param list list to get elemnt from
 @return pointer to the element
 */
void* get_last_element(List* list){
    return get_element(list, LAST_INDEX_OF_LIST(list));
}
/**
 free a list's memory
 
 @param list the list to free
 */
void free_list(List* list){
    
    free(list->array);
    free(list);
}
