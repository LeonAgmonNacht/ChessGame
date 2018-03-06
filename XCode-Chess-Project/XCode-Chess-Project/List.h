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
typedef struct List{
    char* array;
    size_t arrayMaxSize;
    size_t arrayElementsCount;
    int sizeOfElement;
} List;


/**
 initialize list

 @param initialSize inital list size
 @param sizeOfElement size of element of list
 @return List with proper atributes
 */
List* init_list(size_t initialSize, int sizeOfElement);

bool insert_item(List* list,void* element);


/**
 free a list's memory

 @param list the list to free
 */
void free_list(List* list);


#endif /* ListImplemenation_h */

