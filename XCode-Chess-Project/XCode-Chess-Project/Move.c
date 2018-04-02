//
//  Move.c
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 26/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "Move.h"
#include <stdlib.h>

void* copy_move(void* move){
    Move* newMove = malloc(sizeof(Move));
    Move* oldMove = move;
    newMove->cell = oldMove->cell;
    newMove->moveType = oldMove->moveType;
    return newMove;
}

void* copy_detailed_move(void* detailedMoveToCopy){
    DetailedMove* oldDetailedMove = detailedMoveToCopy;
    DetailedMove* copiedDetailedMove = malloc(sizeof(DetailedMove));
    copiedDetailedMove->move = oldDetailedMove->move;
    copiedDetailedMove->fromCell = oldDetailedMove->fromCell;
    return copiedDetailedMove;
}
/**
 Returns true iff the 2 cells are equal (row and col of both cells are equal)
 */
bool are_cells_equal(Cell* firstCell, Cell* secondCell) {
  
    return ((firstCell->row == secondCell->row) && (firstCell->column ==  secondCell->column));
}

