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
    
    for(row; row < 8; row++)
    {
        coloum = row%2;
        x = x + coloum;
        for(coloum; coloum < 4+(row%2); coloum++)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            
            rect.w = darea.w/8;
            rect.h = darea.h/8;
            rect.x = x * rect.w;
            rect.y = row * rect.h;
            x = x + 2;
            SDL_RenderFillRect(renderer, &rect);
        }
        x=0;
    }
    SDL_RenderPresent(renderer);
}
