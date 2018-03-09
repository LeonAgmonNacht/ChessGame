//
//  ChessGameUtils.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef ChessGameUtils_h
#define ChessGameUtils_h
#include <stdlib.h>
#include <stdio.h>
#include "ChessGame.h"

bool verify_valid_start_pos_move(ChessGame* game, Cell* cell);

bool verify_valid_end_pos_move(ChessGame* game, Cell* startCell, Cell* destCell);
/**
 Preforms a move, updates the UI/Console if needed.
 */
void preform_chess_game_move(ChessGame*game, Cell* startCell, Cell* destCell);
#endif /* ChessGameUtils_h */
