//
//  ChessGameMovesValidator.h
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 28/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef ChessGameMovesValidator_h
#define ChessGameMovesValidator_h

#include <stdio.h>
#include "List.h"
typedef struct Cell{
    int row;
    int column;
}Cell;

List* get_posibble_moves(void);

#endif /* ChessGameMovesValidator_h */
