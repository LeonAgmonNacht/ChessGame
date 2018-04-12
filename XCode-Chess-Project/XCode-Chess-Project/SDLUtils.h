//
//  SDLUtils.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef SVDUtils_h
#define SVDUtils_h
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>
#include "List.h"
#define BOARD_SIZE 8
# define YES_BUTTON_ID 1
# define NO_BUTTON_ID 2
# define CANCEL_BUTTON_ID 0

/**
 A struct representing a cell and a color.
 
 */
typedef struct {
    int r;
    int g;
    int b;
    int a;
    int row;
    int col;
} CellColor;

/**
 Present a SDL_ShowMessageBox with info that a check has occurred.
 */
void present_check_dialog(void);
/**
 Present a SDL_ShowMessageBox with info that a checkmate has occurred.
 */
void present_checkmate_dialog(void);
/**
 Present a SDL_ShowMessageBox in which the user can choose that he wants to save the current game.
 */
void present_exit_game_dialog(int* buttonid);
/**
 Draw an 8X8 chess surface starting in the left corner with the size gameBoardSize using the renderer renderer.
 ColoredCells is a list of CellColor. These cells will be coloured with the given color data.
 */
void draw_chess_surface(SDL_Renderer * renderer, int gameBoardSize, List* coloredCells);

/**
 Load the texture of a bmp image in a given path to the given rederer and return it.
 */
SDL_Texture* load_texture(const char* bmp_path, SDL_Renderer* renderer);

/**
 Check if (x,y) point is in rect, return true iff it is.
 */
bool is_in_rect(int x, int y, SDL_Rect* rect);


#endif /* SVDUtils_h */
