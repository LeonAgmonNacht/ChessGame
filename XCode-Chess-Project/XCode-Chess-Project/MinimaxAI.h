//
//  MinimaxAI.h
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 25/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef MinimaxAI_h
#define MinimaxAI_h
#include "ChessBoard.h"
#include "Move.h"
#include "ChessGamesLogic.h"
#include <stdbool.h>
#include <stdio.h>
DetailedMove* get_best_move(ChessBoard* board,bool isWhite,int depth);
#endif /* MinimaxAI_h */
