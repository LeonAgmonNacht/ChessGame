//
//  MainMenuScreen.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 04/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "MainMenuScreen.h"
#include "SDLUtils.h"
#include "SDLUtils.h"
#include <stdbool.h>

// MARK: Window Related Consts:


#define MAIN_MENU_WIN_TITLE "Main Menu"
#define MAIN_MENU_WIN_W 400
#define MAIN_MENU_WIN_H 400
#define BUTTONS_WIDTH 100
#define BUTTONS_HEIGHT 50

// MARK: Textures Rects:

#define NEW_GAME_RECT &(SDL_Rect){(MAIN_MENU_WIN_W/2)-(BUTTONS_WIDTH/2),50,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define LOAD_GAME_RECT &(SDL_Rect){(MAIN_MENU_WIN_W/2)-(BUTTONS_WIDTH/2),150,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define QUIT_GAME_RECT &(SDL_Rect){(MAIN_MENU_WIN_W/2)-(BUTTONS_WIDTH/2),250,BUTTONS_WIDTH,BUTTONS_HEIGHT}

/**
 Creates the texture of the new game button and adds it to the window.
 */
void _init_new_game_button(SDL_Renderer* renderer) {
    SDL_Texture* new_game_button = load_texture("./GUI-Resources/new_button.bmp", renderer);
    SDL_RenderCopy(renderer, new_game_button, NULL, NEW_GAME_RECT);
    SDL_DestroyTexture(new_game_button);
}
/**
 Creates the texture of the load game button and adds it to the window.
 */
void _init_load_game_button(SDL_Renderer* renderer) {
    SDL_Texture* load_game_button = load_texture("./GUI-Resources/load_button.bmp", renderer);
    SDL_RenderCopy(renderer, load_game_button, NULL, LOAD_GAME_RECT);
    SDL_DestroyTexture(load_game_button);
}
/**
 Creates the texture of the new quit game and adds it to the window.
 */
void _init_quit_game_button(SDL_Renderer* renderer) {
    SDL_Texture* quit_game_button = load_texture("./GUI-Resources/quit_button.bmp", renderer);
    SDL_RenderCopy(renderer, quit_game_button, NULL, QUIT_GAME_RECT);
    SDL_DestroyTexture(quit_game_button);
}

/**
 Init a main menu screen, note that the screen will be presented only when calling wait_for_action.
 */
MainMenu* init_main_menu() {
    MainMenu* menu = (MainMenu *) malloc(sizeof(MainMenu));
    menu->window = SDL_CreateWindow(
                                    MAIN_MENU_WIN_TITLE,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    MAIN_MENU_WIN_W,
                                    MAIN_MENU_WIN_H,
                                    SDL_WINDOW_OPENGL);

    menu->windowRenderer = SDL_CreateRenderer(menu->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(menu->windowRenderer, 255, 255, 255, 0);
    SDL_RenderClear(menu->windowRenderer);
    
    _init_new_game_button(menu->windowRenderer);
    _init_load_game_button(menu->windowRenderer);
    _init_quit_game_button(menu->windowRenderer);
    
    return menu;
}
/**
 Frees all resources including SDL ones used by the mainMenu
 */
void free_main_menu(MainMenu* screen){
    SDL_DestroyRenderer(screen->windowRenderer);
    SDL_DestroyWindow(screen->window);
    free(screen);
}
/**
 Block until the user chooses an action, when he/she does, return it.
 */
MainMenuAction wait_for_action(MainMenu* menu) {
    SDL_RenderPresent(menu->windowRenderer);
    
    SDL_Event e;
    while (true) {
        
        SDL_WaitEvent(&e);
        if (e.type == SDL_MOUSEBUTTONUP) {
            int y = e.button.y;
            int x = e.button.x;
            if (is_in_rect(x, y, (LOAD_GAME_RECT))) {
                return MenuActionLoadGame;
            }
            else if (is_in_rect(x, y, (QUIT_GAME_RECT))) {
                return MenuActionQuit;
            }
            else if (is_in_rect(x, y, (NEW_GAME_RECT))) {
                return MenuActionNewGame;
            }
        }
    }
}

