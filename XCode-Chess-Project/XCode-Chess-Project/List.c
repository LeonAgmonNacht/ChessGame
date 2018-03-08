//
//  List.c
//  XCode-Chess-Project
//
//  Created by Daniel Meltzer on 06/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "List.h"
#include <string.h>

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
 @return List element
 */
List* init_list(size_t initialSize, int sizeOfElement){
    List* newList = malloc(sizeof(List));
    newList->array = malloc(initialSize*sizeOfElement);
    newList->arrayElementsCount = 0;
    newList->arrayMaxSize = initialSize;
    newList->sizeOfElement = sizeOfElement;
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
    char* newArrayPointer = realloc(list->array, list->arrayMaxSize*2);
    if(newArrayPointer == NULL){
        if(!_expand_array_for_one_element(list)){
            return false;
        }
    }
    else{
        list->array = newArrayPointer;
        list->arrayMaxSize = list->arrayMaxSize*2;
    }
    return true;
}


/**
 insert an item to the list

 @param list the list to insert an item to
 @param element the element to insert
 @return true - if the isnert succeded , false - if the array is fuel and couldn't exapnd it
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
free a list's memory

@param list the list to free
*/
void free_list(List* list){
    
    free(list->array);
    free(list);
}
