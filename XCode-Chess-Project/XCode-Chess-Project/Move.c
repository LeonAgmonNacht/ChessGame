//
//  Move.c
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 26/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "Move.h"

/**
 Returns true iff the 2 cells are equal (row and col of both cells are equal)
 */
bool cellsAreEqual(Cell* fCell, Cell* sCell) {
    return (fCell->row == sCell->row) && (fCell->column == fCell->column);
}
