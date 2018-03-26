//
//  Move.h
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 26/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef Move_h
#define Move_h

#include <stdio.h>
#include <stdbool.h>
/**
 a struct representing a Cell/Tile in the game.
 */
typedef struct Cell{
    int row;
    int column;
} Cell;
typedef enum MoveType{
    
    ThreatendType,// a move where the player is threatend
    CaptureType,// the move captures a player
    ThreatendCaptureType,// the move captures and get threatend,
    RegularType   //not specified above
}MoveType;
typedef struct Move{
    Cell cell;// cell to move to
    MoveType moveType; //the type of move
}Move;

typedef struct DetailedMove{
    Cell fromCell;
    Move move;
}DetailedMove;

/**
 Returns true iff the 2 cells are equal (row and col of both cells are equal)
 */
bool cellsAreEqual(Cell* fCell, Cell* sCell);
#endif /* Move_h */
