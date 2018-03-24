//
//  Error.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 22/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef Error_h
#define Error_h

#include <stdio.h>
#include <stdbool.h>

typedef struct _error {
    char description;
    bool recoverable; // Can the error be recovered or is an assert needed.
    int code; // Used if multiple errors can occurr in the same method, this number will be used to code different behaviors for different failures within the same method.
    
} Error;

#endif /* Error_h */
