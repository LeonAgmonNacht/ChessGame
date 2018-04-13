//
//  SDLUtils.c
//  FinalProject-Chess
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "SDLUtils.h"

# define BLACK_TILE_COLOR 210, 105, 30, 1
# define WHITE_TILE_COLOR 255,255,255,1
# define CHECK_TITLE "Check!"
# define CHECKMATH_TITLE "Checkmate!"
# define EXIT_GAME_TITLE "Unsaved Game!"
# define EXIT_GAME_TEXT "Would you like to save the current game before exiting?"
# define YES_BUTTON_TEXT "Yes"
# define NO_BUTTON_TEXT "No"
# define CANCEL_BUTTON_TEXT "Cancel"
# define OK_BUTTON_TEXT "Ok"

/**
 Draw an 8X8 chess surface starting in the left corner with the size gameBoardSize using the renderer renderer.
 ColoredCells is a list of CellColor. These cells will be coloured with the given color data.
 */
void draw_chess_surface(SDL_Renderer * renderer, int gameBoardSize, List* coloredCells) {
    int row = 0,coloum = 0,x = 0;
    SDL_Rect rect; SDL_Rect darea = { .x = 0, .y = 0, .w = gameBoardSize, .h = gameBoardSize };
    
    SDL_SetRenderDrawColor(renderer, BLACK_TILE_COLOR);
    SDL_RenderFillRect(renderer, &darea);
    
    for(; row < BOARD_SIZE; row++) {
        coloum = row%2;
        x = x + coloum;
        for(; coloum < (BOARD_SIZE/2)+(row%2); coloum++) {
            SDL_SetRenderDrawColor(renderer, WHITE_TILE_COLOR);
            
            rect.w = darea.w/BOARD_SIZE;
            rect.h = darea.h/BOARD_SIZE;
            rect.x = x * rect.w;
            rect.y = row * rect.h;
            x = x + 2;
            SDL_RenderFillRect(renderer, &rect);
        }
        x=0;
    }
    if (coloredCells != NULL) {
        for (int i = 0; i<(int)get_items_count(coloredCells); i++) {
            CellColor cell = *(CellColor*)get_element(coloredCells, (size_t)i);
            rect.w = darea.w/BOARD_SIZE;
            rect.h = darea.h/BOARD_SIZE;
            rect.x = cell.col * rect.w;
            rect.y = cell.row * rect.h;
            SDL_SetRenderDrawColor(renderer, (unsigned char)cell.r, (unsigned char)cell.g, (unsigned char)cell.b, (unsigned char)cell.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
/**
 Load the texture of a bmp image in a given path to the given rederer and return it.
 */
SDL_Texture* load_texture(const char* bmp_path, SDL_Renderer* renderer) {
    SDL_Surface* surf = SDL_LoadBMP(bmp_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}

/**
 Check if (x,y) point is in rect, return true iff it is.
 */
bool is_in_rect(int x, int y, SDL_Rect* rect) {
    
    return ((x > rect->x) &&
            (x < rect->x + rect->w) &&
            (y > rect->y) &&
            (y < rect->y + rect->h));
}

/**
 Present a SDL_ShowMessageBox with info that a check has occurred.
 */
void present_check_dialog() {
    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, OK_BUTTON_TEXT },
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        CHECK_TITLE,
        "",
        SDL_arraysize(buttons),
        buttons,
        NULL
    };
    int buttonid;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
}
/**
 Present a SDL_ShowMessageBox with info that a checkmate has occurred.
 */
void present_checkmate_dialog() {
    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, OK_BUTTON_TEXT },
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        CHECKMATH_TITLE,
        "",
        SDL_arraysize(buttons),
        buttons,
        NULL
    };
    int buttonid;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
}

/**
 Present a SDL_ShowMessageBox in which the user can choose that he wants to save the current game.
 */
void present_exit_game_dialog(int* buttonid) {
    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, YES_BUTTON_ID, YES_BUTTON_TEXT },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, CANCEL_BUTTON_ID, CANCEL_BUTTON_TEXT },
        { 0, NO_BUTTON_ID, NO_BUTTON_TEXT }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        EXIT_GAME_TITLE,
        EXIT_GAME_TEXT,
        SDL_arraysize(buttons),
        buttons,
        NULL
    };
    SDL_ShowMessageBox(&messageboxdata, buttonid);}

