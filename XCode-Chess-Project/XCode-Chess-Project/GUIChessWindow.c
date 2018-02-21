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
    draw_chess_surface(window->window_renderer, GAMEGUIBOARDSIZE);
};

guiChessWindow* init_gui_window() {
    guiChessWindow* gui_window = (guiChessWindow *) malloc(sizeof(guiChessWindow));
    gui_window->window = SDL_CreateWindow(
                                          WIN_TITLE,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIN_WIDTH,
                                          WIN_HEIGHT,
                                          SDL_WINDOW_OPENGL);
    gui_window->window_renderer = SDL_CreateRenderer(gui_window->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(gui_window->window_renderer);
    
    return gui_window;
}
