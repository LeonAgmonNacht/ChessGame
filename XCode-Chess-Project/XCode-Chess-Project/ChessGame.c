//
//  ChessGame.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "ChessGame.h"
#include "GUIChessWindow.h"
#include "ChessBoard.h"

// TODO: Doc, add modes ... (mode is console or gui)
// TODO: check for fails

chessGame* init_game(int mode) {
    
    // MEM:
    
    chessGame * game = (chessGame *) malloc(sizeof(chessGame));

    // INIT:
    
    game->board = init_game_board(mode);
    
    if (mode == GAME_MODE_WITH_GUI) {
        game->boardWindow = init_gui_window();
    }
    
    return game;
}
