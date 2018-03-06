//
//  main.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "ChessGame.h"
#include "MainMenuScreen.h"
#include "NewGameMenuScreen.h"
#include "LoadGameScreen.h"
// TODO: rename all clases to capital at first
// TODO: consider adding a quit_game method.

ChessGame* reset_console_game() {
    // Game settings state:
    GameSettings* settings = get_game_settings();
    
    if (settings == NULL) { // aka quit
        free(settings); // TODO: create costum free method
        return NULL;
    }
    
    settings->guiMode = GAME_MODE_CONSOLE;
    
    ChessGame * game = init_game(settings);
    return game;
}


ChessGame* reset_gui_game() {
    MainMenu* menu = init_main_menu();
    MainMenuAction* action = wait_for_action(menu);

    if (action == MenuActionNewGame) {
        SettingsScreen* GameSettingsScreen = init_settings_screen();
        GameSettings* newGameSettings = wait_for_start(GameSettingsScreen);
        ChessGame * game = init_game(newGameSettings);
        return game;
    }
    else if (action == MenuActionLoadGame) {
        LoadGameScreen* load_screen = init_load_game_screen();
        ChessGame* game = wait_for_game(load_screen);
        return game;
    }
    else { // Action is Quit
        
    }
    free_main_menu(menu);
    
    return NULL;
}

int main(int argc, const char * argv[]) {
    
    bool is_console_game = false;
    
    // Print initial game message:
    printf(" Chess\n-------\n"); // TODO: get from argv[].
    
    // Get game:
    ChessGame* game;
    if (is_console_game) {
        
        // Get game settings:
        game = reset_console_game();
        play_chess_game(game);
        if (game == NULL) {
            printf("Exiting...\n");
            SDL_Quit();
            return 0;
        }
        free_game(game);
    }
    else {
        
        // Initilize Game:
        
        SDL_Init(SDL_INIT_VIDEO);
        
        // Play game:
        
        game = reset_gui_game();
        if (game != NULL) play_chess_game(game);
        
        // Release mem and close SDL:
        free_game(game);
        SDL_Quit();
    }
    
}
