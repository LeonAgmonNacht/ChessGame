//
//  GUIChessWindow.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "GUIChessWindow.h"
#include "ChessBoard.h"

void draw_chess_board_according_to_state(chessBoard * board, guiChessWindow * window) {
    
};

guiChessWindow* init_gui_window() {
    guiChessWindow* window = (guiChessWindow *) malloc(sizeof(guiChessWindow));
    return window;
}
