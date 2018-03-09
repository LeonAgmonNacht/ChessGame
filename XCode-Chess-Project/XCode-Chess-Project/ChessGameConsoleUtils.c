//
//  ChessGameConsoleUtils.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ChessGameConsoleUtils.h"
#include "ChessGameUtils.h"

/**
 Play a console game until it is finished. Returns the reason for ending game.
 NOTE: a load/save/undo/move_piece commands are handled internally.
 */
GameFinishedStatusEnum play_console_game(ChessGame* game) {
    Cell* cell = NULL; // Will be used to store the first-cell-clicked by the user, next cell-click will cause a move.
    bool gameHasEnded = false; // true if the game has ended -> disables moving the pieces but allowing the user to choose his next action.
    
    // Handle first move:
    if (game->currentPlayerWhite) {
        print_board_to_file(game->board, stdout);
        
    }
    
    while (true) {
        
    }
    
}
