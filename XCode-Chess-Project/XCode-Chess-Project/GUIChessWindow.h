//
//  GUIChessWindow.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef GUIChessWindow_h
#define GUIChessWindow_h

#include <stdio.h>

typedef struct _gui_chess_window {
    
} guiChessWindow;

void draw_chess_board_according_to_state(chessBoard * board, guiChessWindow * window);

guiChessWindow* init_gui_window();

#endif /* GUIChessWindow_h */
