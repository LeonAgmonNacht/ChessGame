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
#define BOARD_SIZE 8

/**
 Draw an 8X8 chess surface starting in the left corner with the size gameBoardSize using the renderer renderer.
 */
void draw_chess_surface(SDL_Renderer * renderer, int gameBoardSize);

/**
 Load the texture of a bmp image in a given path to the given rederer and return it.
 */
SDL_Texture* load_texture(const char* bmp_path, SDL_Renderer* renderer);

/**
 Check if (x,y) point is in rect, return true iff it is.
 */
bool is_in_rect(int x, int y, SDL_Rect* rect);


#endif /* SVDUtils_h */
