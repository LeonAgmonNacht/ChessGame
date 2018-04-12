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
#define SAVE_GAME_WIN_TITLE "Save Game"
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
void _draw_slots_buttons(SDL_Renderer* renderer, int pageNum, bool shouldLoad) {
    char* imgBaseName = shouldLoad ? "./GUI-Resources/game_slots_%d.bmp" : "./GUI-Resources/save_game_slots_%d.bmp";
    char * imgPath = (char*)malloc(strlen(imgBaseName));
    if (shouldLoad) sprintf(imgPath, "./GUI-Resources/game_slots_%d.bmp", pageNum);
    else sprintf(imgPath, "./GUI-Resources/save_game_slots_%d.bmp", pageNum);
    SDL_Texture* slotsButton = load_texture(imgPath, renderer);
    SDL_RenderCopy(renderer, slotsButton, NULL, SLOTS_RECT);
    SDL_DestroyTexture(slotsButton);
    free(imgPath);
}

/**
 Creates the arrows button
 */
void _draw_arrows_buttons(SDL_Renderer* renderer) {
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
void _draw_back_button(SDL_Renderer* renderer) {
    SDL_Texture* playerColor = load_texture("./GUI-Resources/back_button.bmp", renderer);
    SDL_RenderCopy(renderer, playerColor, NULL, BACK_BUTTON_RECT);
    SDL_DestroyTexture(playerColor);
}

/**
 Refresh aka re-render the view with the given params.
 */
void _refresh_view(SDL_Renderer* renderer, int pageNum, bool shouldLoad) {
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // White
    SDL_RenderClear(renderer);
    _draw_slots_buttons(renderer, pageNum, shouldLoad);
    _draw_arrows_buttons(renderer);
    _draw_back_button(renderer);
}

/**
 Init all data and textures. NOTE that the data will be presented only when calling wait_for_game
 The boolean shouldLoad controls which image should be presented: if true a load from slot image will be presented,
 if it is false, a save to slot image will be presented.
 */
LoadGameScreen* init_load_game_screen(bool shouldLoad) {
    LoadGameScreen* loadScreen = (LoadGameScreen*)malloc(sizeof(LoadGameScreen));
    loadScreen->window = SDL_CreateWindow(
                                    shouldLoad == true ? LOAD_GAME_WIN_TITLE : SAVE_GAME_WIN_TITLE,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    LOAD_GAME_WIN_W,
                                    LOAD_GAME_WIN_H,
                                    SDL_WINDOW_OPENGL);
    
    loadScreen->windowRenderer = SDL_CreateRenderer(loadScreen->window, -1, SDL_RENDERER_ACCELERATED);
    
    
    _refresh_view(loadScreen->windowRenderer, 1, shouldLoad);
    return loadScreen;

}
/**
 Frees all resources used by the load game gui screen.
 */
void free_load_game_screen(LoadGameScreen* screen) {
    SDL_DestroyRenderer(screen->windowRenderer);
    SDL_DestroyWindow(screen->window);
    free(screen);
}

/**
 Waits for the user to chose a slot, returns the slot index. If the back button was clicked, returns -1;
 The boolean shouldLoad controls which image should be presented: if true a load from slot image will be presented,
 if it is false, a save to slot image will be presented.
 */
int wait_for_slot_choice(LoadGameScreen* screen, bool shouldLoad) {
    int pageNum = 1;
    
    SDL_RenderPresent(screen->windowRenderer);

    SDL_Event e;
    while (true) {
        
        SDL_WaitEvent(&e);
        if (e.type == SDL_MOUSEBUTTONUP) {
            int y = e.button.y;
            int x = e.button.x;
            
            if (is_in_rect(x, y, UP_ARROW_RECT)) {
                if (pageNum > 1) pageNum--;
            }
            else if (is_in_rect(x, y, DOWN_ARROW_RECT)) {
                if (pageNum < NUM_PAGES) pageNum ++;
            }
            else if (is_in_rect(x, y, SLOTS_RECT)) {
                int slotNum = 1 + (pageNum-1)*NUM_SLOTS_IN_SCREEN + ((y - *SLOTS_RECT.y)/(*SLOTS_RECT.h/NUM_SLOTS_IN_SCREEN));
                return slotNum;
            }
            else if (is_in_rect(x, y, BACK_BUTTON_RECT)) {
                return -1;
            }
            _refresh_view(screen->windowRenderer, pageNum, shouldLoad);
            SDL_RenderPresent(screen->windowRenderer);
        }
    }
    return -1;
}
