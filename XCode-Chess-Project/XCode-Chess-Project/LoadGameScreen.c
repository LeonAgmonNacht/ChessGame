//
//  LoadGameScreen.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 06/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "LoadGameScreen.h"
#include "SDLUtils.h"
#include "ChessGame.h"

#define LOAD_GAME_WIN_TITLE "Load Game"
#define NUM_SLOTS_IN_SCREEN 5
#define NUM_SLOTS_TOTAL 5
#define NUM_PAGES NUM_SLOTS_TOTAL/NUM_SLOTS_IN_SCREEN
#define LOAD_GAME_WIN_W 400
#define LOAD_GAME_WIN_H 400
#define TEXTURES_PADDING 25
#define SLOTS_WIDTH_HEIGHT 300
#define ARROWS_WIDTH_HEIGHT 60
#define BACK_BUTTON_H 50
#define BACK_BUTTON_W 100
#define BACK_PADDING 35
#define SLOTS_RECT &(SDL_Rect){TEXTURES_PADDING,TEXTURES_PADDING,SLOTS_WIDTH_HEIGHT,SLOTS_WIDTH_HEIGHT}
#define UP_ARROW_RECT &(SDL_Rect){SLOTS_WIDTH_HEIGHT+TEXTURES_PADDING,TEXTURES_PADDING,ARROWS_WIDTH_HEIGHT,ARROWS_WIDTH_HEIGHT}
#define DOWN_ARROW_RECT &(SDL_Rect){SLOTS_WIDTH_HEIGHT+TEXTURES_PADDING,TEXTURES_PADDING+ARROWS_WIDTH_HEIGHT,ARROWS_WIDTH_HEIGHT,ARROWS_WIDTH_HEIGHT}
#define BACK_BUTTON_RECT &(SDL_Rect){TEXTURES_PADDING,SLOTS_WIDTH_HEIGHT+BACK_PADDING,BACK_BUTTON_W,BACK_BUTTON_H}

/**
 Creates the texture of the slots
 */
void _draw_slots_buttons(SDL_Renderer* renderer, SDL_Window* window, int pageNum) {
    char * imgPath = (char*)malloc(strlen("./GUI-Resources/game_slots_1.bmp"));
    sprintf(imgPath, "./GUI-Resources/game_slots_%d.bmp", pageNum);
    SDL_Texture* slotsButton = load_texture(imgPath, renderer);
    SDL_RenderCopy(renderer, slotsButton, NULL, SLOTS_RECT);
    SDL_DestroyTexture(slotsButton);
    free(imgPath);
}

/**
 Creates the arrows button
 */
void _draw_arrows_buttons(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_Texture* downArrow = load_texture("./GUI-Resources/arrow_down.bmp", renderer);
    SDL_Texture* upArrow = load_texture("./GUI-Resources/arrow_up.bmp", renderer);
    SDL_RenderCopy(renderer, upArrow, NULL, UP_ARROW_RECT);
    SDL_RenderCopy(renderer, downArrow, NULL, DOWN_ARROW_RECT);
    SDL_DestroyTexture(upArrow);
    SDL_DestroyTexture(downArrow);
}

/**
 Draws the back game button
 */
void _draw_back_button(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_Texture* playerColor = load_texture("./GUI-Resources/back_button.bmp", renderer);
    SDL_RenderCopy(renderer, playerColor, NULL, BACK_BUTTON_RECT);
    SDL_DestroyTexture(playerColor);
}

void _refresh_view(SDL_Renderer* renderer, SDL_Window* window, int pageNum) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // White
    SDL_RenderClear(renderer);
    _draw_slots_buttons(renderer, window, pageNum);
    _draw_arrows_buttons(renderer, window);
    _draw_back_button(renderer, window);
}

/**
 Init all data and textures. NOTE that the data will be presented only when calling wait_for_game
 */
LoadGameScreen* init_load_game_screen() {
    LoadGameScreen* loadScreen = (LoadGameScreen*)malloc(sizeof(LoadGameScreen));
    loadScreen->window = SDL_CreateWindow(
                                    LOAD_GAME_WIN_TITLE,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    LOAD_GAME_WIN_W,
                                    LOAD_GAME_WIN_H,
                                    SDL_WINDOW_OPENGL);
    
    loadScreen->windowRenderer = SDL_CreateRenderer(loadScreen->window, -1, SDL_RENDERER_ACCELERATED);
    
    
    _refresh_view(loadScreen->windowRenderer, loadScreen->window, 1);
    return loadScreen;

}

void free_load_game_screen(LoadGameScreen* screen) {
    
}

ChessGame* _load_game_from_slot(int slotNum) {
    return NULL;
}

ChessGame* wait_for_game(LoadGameScreen* screen) {
    int pageNum = 1;
    
    SDL_RenderPresent(screen->windowRenderer);

    SDL_Event e;
    while (true) {
        
        SDL_WaitEvent(&e);
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int y = e.button.y;
            int x = e.button.x;
            
            if (is_in_rect(x, y, UP_ARROW_RECT)) {
                if (pageNum > 1) pageNum--;
            }
            else if (is_in_rect(x, y, DOWN_ARROW_RECT)) {
                if (pageNum < NUM_PAGES) pageNum ++;
            }
            else if (is_in_rect(x, y, SLOTS_RECT)) {
                int slotNum = 1 + pageNum*NUM_SLOTS_IN_SCREEN + ((y - *SLOTS_RECT.y)/(*SLOTS_RECT.h/NUM_SLOTS_IN_SCREEN));
                ChessGame* game = _load_game_from_slot(slotNum);
                if (game != NULL) { // Slot is taken, and a game was loaded
                    return game;
                }
            }
            else if (is_in_rect(x, y, BACK_BUTTON_RECT)) {
                return NULL;
            }
            _refresh_view(screen->windowRenderer, screen->window, pageNum);
            SDL_RenderPresent(screen->windowRenderer);
        }
    }
    return NULL;
}
