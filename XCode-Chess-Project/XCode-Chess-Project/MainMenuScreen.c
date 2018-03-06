//
//  MainMenuScreen.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 04/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "MainMenuScreen.h"
#include <SDL.h>
#include <SDL_video.h>

MainMenu* init_main_menu() {
    MainMenu* menu = (MainMenu *) malloc(sizeof(MainMenu));
//    gui_window->window = SDL_CreateWindow(
//                                          WIN_TITLE,
//                                          SDL_WINDOWPOS_CENTERED,
//                                          SDL_WINDOWPOS_CENTERED,
//                                          WIN_WIDTH,
//                                          WIN_HEIGHT,
//                                          SDL_WINDOW_OPENGL);
//    gui_window->window_renderer = SDL_CreateRenderer(gui_window->window, -1, SDL_RENDERER_ACCELERATED);
//    SDL_RenderClear(gui_window->window_renderer);
    return menu;
}
void free_main_menu(MainMenu* screen){
    free(screen);
}

MainMenuAction* wait_for_action(MainMenu* menu) {
    return NULL;
}
