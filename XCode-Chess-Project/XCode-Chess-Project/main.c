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

/**
 Asks the user in stdin for the game settings and returns the entered ones.
 */
ChessGame* reset_console_game() {
    // Game settings state:
    GameSettings* settings = get_game_settings();
    
    if (settings == NULL) { // aka quit
        return NULL;
    }
    
    ChessGame * game = init_game(settings);
    return game;
}

/**
 Go through the series of screens that conduct a chess game, returns the coducted game.
 */
ChessGame* reset_gui_game() {
    MainMenu* menu = init_main_menu();
    // Wait for the user to choose his action from the main menu screen:
    MainMenuAction action = wait_for_action(menu);
    free_main_menu(menu);
    
    if (action == MenuActionNewGame) { // Go to new game/settings screen
        SettingsScreen* settingsScreen = init_settings_screen();
        GameSettings* newGameSettings = wait_for_start(settingsScreen);
        free_settings_screen(settingsScreen);
        if (newGameSettings == NULL) { // NULL means Back was pressed
            return reset_gui_game(); // Restart proccess
        }
        ChessGame * game = init_game(newGameSettings);
        return game;
    }
    else if (action == MenuActionLoadGame) { // User wishs to load a game, present the load screen
        LoadGameScreen* loadScreen = init_load_game_screen();
        ChessGame* game = wait_for_game(loadScreen);
        free_load_game_screen(loadScreen);
        if (game == NULL) {
            return reset_gui_game(); // Restart proccess
        }
        return game;
    }
    else { // Action is Quit
        
    }
    
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
