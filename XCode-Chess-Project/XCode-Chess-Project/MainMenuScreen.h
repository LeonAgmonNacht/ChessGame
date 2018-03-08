//
//  MainMenuScreen.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 04/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef MainMenuScreen_h
#define MainMenuScreen_h

#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>

/**
 Represents a main menu screen in the GUI application.
 */
typedef struct _main_menu {
    SDL_Window *window;
    SDL_Renderer *windowRenderer;
}
MainMenu;

/**
 Init a main menu screen, note that the screen will be presented only when calling wait_for_action.
 */
MainMenu* init_main_menu(void);

void free_main_menu(MainMenu* screen);

/**
 Specifies the possible actions that may occurr in the main menu screen.
 */
typedef enum {
    MenuActionNewGame,
    MenuActionLoadGame,
    MenuActionQuit
} MainMenuAction;

/**
 Block until the user chooses an action, when he/she does, return it.
 */
MainMenuAction wait_for_action(MainMenu* menu);
#endif /* MainMenuScreen_h */
