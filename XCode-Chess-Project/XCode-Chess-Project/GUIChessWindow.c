//
//  GUIChessWindow.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//
#include <SDL.h>
#include <SDL_video.h>
#include "GUIChessWindow.h"
#include "SDLUtils.h"
#define WIN_TITLE "Chess Game"
#define WIN_WIDTH 1024
#define WIN_HEIGHT 768
#define GAMEGUIBOARDSIZE 768
#define BOARD_SIZE 8
#define PIECES_COUNT 6
#define PLAYERS_COUNT 2
#define WHITE_PIECES_TEXTURE_INDEX 1
#define BLACK_PIECES_TEXTURE_INDEX 0
#define PIECE_SIZE GAMEGUIBOARDSIZE/BOARD_SIZE

#define BUTTONS_WIDTH 100
#define BUTTONS_HEIGHT 50
#define BUTTONS_PADDING 25
#define BUTTONS_X GAMEGUIBOARDSIZE + BUTTONS_PADDING
#define RESTART_RECT &(SDL_Rect){BUTTONS_X,BUTTONS_PADDING,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define SAVE_RECT &(SDL_Rect){BUTTONS_X,BUTTONS_PADDING*2+BUTTONS_HEIGHT,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define LOAD_RECT &(SDL_Rect){BUTTONS_X,BUTTONS_PADDING*3+BUTTONS_HEIGHT*2,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define UNDO_RECT &(SDL_Rect){BUTTONS_X,BUTTONS_PADDING*4+BUTTONS_HEIGHT*3,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define MAIN_MENU_RECT &(SDL_Rect){BUTTONS_X,BUTTONS_PADDING*5+BUTTONS_HEIGHT*4,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define QUIT_RECT &(SDL_Rect){BUTTONS_X,BUTTONS_PADDING*6+BUTTONS_HEIGHT*5,BUTTONS_WIDTH,BUTTONS_HEIGHT}

/**
 the paths array is organized in the following way: <blacks array>,<whites array> in each array the paths are organized by the order of pieces types in PieceType enum
 */
#define IMGS_PATHS_FOR_PIECES_ARRAY {{"./GUI-Resources/Chess_kdt60.bmp","./GUI-Resources/Chess_qdt60.bmp","./GUI-Resources/Chess_rdt60.bmp","./GUI-Resources/Chess_bdt60.bmp","./GUI-Resources/Chess_ndt60.bmp","./GUI-Resources/Chess_pdt60.bmp"},{"./GUI-Resources/Chess_klt60.bmp","./GUI-Resources/Chess_qlt60.bmp","./GUI-Resources/Chess_rlt60.bmp","./GUI-Resources/Chess_blt60.bmp","./GUI-Resources/Chess_nlt60.bmp","./GUI-Resources/Chess_plt60.bmp"}}
/**
 Get SDL_Point (x,y) index in renderer for piece index (row, col)
 */
SDL_Rect* _get_location_per_index(int row, int col, int gameBoardSize) {
    int tileSize = (gameBoardSize/BOARD_SIZE);
    int xLoc = tileSize*col;
    int yLoc = tileSize*row;
    SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    rect->x = xLoc; rect->y = yLoc; rect->w = rect->h = PIECE_SIZE;
    return rect;
}

/**
 get a texture for game piece

 @param chessWindow the chess window conatining all the textures
 @param gamePiece the game piece to get the texture for
 @return an SDL_Texture item matching to the given gamePiece color and type
 */
static SDL_Texture* _get_texture_for_game_piece(GuiChessWindow* chessWindow,GamePiece* gamePiece){
   return chessWindow->TexturesForAllGameGraphicalPieces[gamePiece->isWhite ? WHITE_PIECES_TEXTURE_INDEX:BLACK_PIECES_TEXTURE_INDEX][gamePiece->typeOfGamePiece];
}
void _draw_chess_piece(SDL_Rect* rect, SDL_Texture* texture, GuiChessWindow* window) {
    SDL_RenderCopy(window->windowRenderer, texture, NULL, rect);
}

void _draw_chess_pieces(GuiChessWindow * window, ChessBoard * board, int gameBoardSize) {
    for (int row = 0; row < BOARD_SIZE; row ++) {
        for (int col = 0; col < BOARD_SIZE; col ++) {
            SDL_Rect * rect = _get_location_per_index(row, col, gameBoardSize);
            if (board->boardData[row][col] != NULL && _get_texture_for_game_piece(window, board->boardData[row][col]) != NULL) {
                _draw_chess_piece(rect,_get_texture_for_game_piece(window, board->boardData[row][col]) , window);
            }
            free(rect);
        }
    }
}

void _draw_buttons(GuiChessWindow* window) {
    
    SDL_Texture* restart = load_texture("./GUI-Resources/restart_button.bmp", window->windowRenderer);
    SDL_Texture* save = load_texture("./GUI-Resources/save_button.bmp", window->windowRenderer);
    SDL_Texture* load = load_texture("./GUI-Resources/load_button.bmp", window->windowRenderer);
    SDL_Texture* undo = load_texture("./GUI-Resources/undo_button.bmp", window->windowRenderer);
    SDL_Texture* mainMenu = load_texture("./GUI-Resources/main_menu_button.bmp", window->windowRenderer);
    SDL_Texture* quit = load_texture("./GUI-Resources/quit_button.bmp", window->windowRenderer);
    SDL_RenderCopy(window->windowRenderer, restart, NULL, RESTART_RECT);
    SDL_RenderCopy(window->windowRenderer, save, NULL, SAVE_RECT);
    SDL_RenderCopy(window->windowRenderer, load, NULL, LOAD_RECT);
    SDL_RenderCopy(window->windowRenderer, undo, NULL, UNDO_RECT);
    SDL_RenderCopy(window->windowRenderer, mainMenu, NULL, MAIN_MENU_RECT);
    SDL_RenderCopy(window->windowRenderer, quit, NULL, QUIT_RECT);

    SDL_DestroyTexture(restart);
    SDL_DestroyTexture(save);
    SDL_DestroyTexture(load);
    SDL_DestroyTexture(undo);
    SDL_DestroyTexture(mainMenu);
    SDL_DestroyTexture(quit);

}

void draw_chess_board_according_to_state(ChessBoard * board, GuiChessWindow * window) {
    SDL_SetRenderDrawColor(window->windowRenderer, 255, 255, 255, 0); // White
    SDL_RenderClear(window->windowRenderer);
    draw_chess_surface(window->windowRenderer, GAMEGUIBOARDSIZE);
    _draw_chess_pieces(window, board, GAMEGUIBOARDSIZE);
    _draw_buttons(window);
    SDL_RenderPresent(window->windowRenderer);
};


/**
 this function enbales us to load the textrues required for the drawing of the pieces of the game.
 the loaded textures will be ordered like the paths aka :
 @warning the texture array is organized in the following way: <blacks array>,<whites array> in each array the paths are organized by the order of pieces types in PieceType enum
 @param gui_window the window of the game
 */
static void load_textures(GuiChessWindow *gui_window) {
    
    static const char* pathsForGrpahicalPieces[PLAYERS_COUNT][PIECES_COUNT] = IMGS_PATHS_FOR_PIECES_ARRAY;
    
    for(int i =0;i<PLAYERS_COUNT;i++){
        for(int j =0;j<PIECES_COUNT;j++){
            SDL_Texture* pieceTexture = load_texture(pathsForGrpahicalPieces[i][j],
                                                     gui_window->windowRenderer);
            gui_window->TexturesForAllGameGraphicalPieces[i][j] = pieceTexture;
        }
    }
}

GuiChessWindow* init_gui_window() {
    GuiChessWindow* gui_window = (GuiChessWindow *) malloc(sizeof(GuiChessWindow));
    gui_window->window = SDL_CreateWindow(
                                          WIN_TITLE,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIN_WIDTH,
                                          WIN_HEIGHT,
                                          SDL_WINDOW_OPENGL);
    gui_window->windowRenderer = SDL_CreateRenderer(gui_window->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(gui_window->windowRenderer);
    
    load_textures(gui_window);
    return gui_window;
}

/**
 Waits until a move has been made or a button was clicked.
 */
ChessWindowAction* wait_for_move_or_action(GuiChessWindow* window) {
    
    return NULL;
}
