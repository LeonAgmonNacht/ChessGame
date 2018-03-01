//
//  SDLUtils.c
//  FinalProject-Chess
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "SDLUtils.h"


void draw_chess_surface(SDL_Renderer * renderer, int gameBoardSize)
{
    int row = 0,coloum = 0,x = 0;
    SDL_Rect rect; SDL_Rect darea = { .x = 0, .y = 0, .w = gameBoardSize, .h = gameBoardSize };
    
    SDL_SetRenderDrawColor(renderer, 210, 105, 30, 1);
    SDL_RenderFillRect(renderer, &darea);
    
    for(; row < BOARD_SIZE; row++) {
        coloum = row%2;
        x = x + coloum;
        for(; coloum < (BOARD_SIZE/2)+(row%2); coloum++) {
            SDL_SetRenderDrawColor(renderer, 255,255,255,1);
            
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
