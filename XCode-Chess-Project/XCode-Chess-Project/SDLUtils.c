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
/**
 Draw an 8X8 chess surface starting in the left corner with the size gameBoardSize using the renderer renderer.
 */
void draw_chess_surface(SDL_Renderer * renderer, int gameBoardSize)
{
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
