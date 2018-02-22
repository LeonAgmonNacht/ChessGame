//
//  GUIChessWindow.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "GUIChessWindow.h"

/**
 Get SDL_Point (x,y) index in renderer for piece index (row, col)
 */
SDL_Rect* _get_location_per_index(int row, int col, int gameBoardSize) {
    int tileSize = (gameBoardSize/BOARD_SIZE);
    int xLoc = tileSize*col - (PIECE_SIZE/2);
    int yLoc = tileSize*row - (PIECE_SIZE/2);
    
    return &(SDL_Rect) {.x = xLoc, .y = yLoc, .w = PIECE_SIZE, .h = PIECE_SIZE};
}

void _draw_chess_board(SDL_Rect* rect, gamePiece* piece, guiChessWindow* window) {
    SDL_RenderCopy(window->window_renderer, piece->texture, NULL, rect);
}

void _draw_chess_pieces(guiChessWindow * window, chessBoard * board, int gameBoardSize) {
    for (int row = 0; row < BOARD_SIZE; row ++) {
        for (int col = 0; col < BOARD_SIZE; col ++) {
            SDL_Rect * rect = _get_location_per_index(row, col, gameBoardSize);
            if (board->boardData[row][col] != NULL && board->boardData[row][col]->texture != NULL) {
                _draw_chess_board(rect, board->boardData[row][col], window);
            }
        }
    }
}

void draw_chess_board_according_to_state(chessBoard * board, guiChessWindow * window) {
    draw_chess_surface(window->window_renderer, GAMEGUIBOARDSIZE);
    _draw_chess_pieces(window, board, GAMEGUIBOARDSIZE);
    SDL_RenderPresent(window->window_renderer);
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
