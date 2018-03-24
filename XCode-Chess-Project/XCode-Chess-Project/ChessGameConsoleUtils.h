//
//  ChessGameConsoleUtils.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef ChessGameConsoleUtils_h
#define ChessGameConsoleUtils_h

#include "ChessGame.h"
#include <stdio.h>

/**
 Play a console game until it is finished. Returns the reason for ending game.
 NOTE: a load/save/undo/move_piece commands are handled internally.
 */
GameFinishedStatusEnum play_console_game(ChessGame* game);

#endif /* ChessGameConsoleUtils_h */
