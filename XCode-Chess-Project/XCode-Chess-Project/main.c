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
        LoadGameScreen* loadScreen = init_load_game_screen(true); // true because we are loading from a slot, and not saving to one.
        int slotIndex = wait_for_slot_choice(loadScreen, true); // true because we are loading from a slot, and not saving to one.
        free_load_game_screen(loadScreen);
        if (slotIndex == -1) { // Back
            return reset_gui_game(); // Restart proccess
        }
        return load_game_from_slot_index(slotIndex, GAME_MODE_WITH_GUI);
    }
    else { // Action is Quit
        
    }
    
    return NULL;
}

/**
 Play a gui game with the given settings, if NULL reset_gui_game function will be called
 */
void play_gui_game(GameSettings* settings) {
    ChessGame* game;
    if (settings == NULL) { game = reset_gui_game();}
    else {game = init_game(settings);}
    
    if (game != NULL) {
        GameFinishedStatusEnum finishedAction = play_chess_game(game);
        if (finishedAction == GameFinishedActionMainMenu) {
            free_game(game);
            return play_gui_game(NULL);
            
        }
        else if (finishedAction == GameFinishedActionReset) {
            GameSettings* settings = clone_game_settings(game->settings);
            free_game(game);
            return play_gui_game(settings);
        }
        else { // Finished action is quit
        free_game(game);
        }
    }
}

void play_console_game() {
    // Get game settings:
    ChessGame* game = reset_console_game();
    if (game != NULL) {
        GameFinishedStatusEnum finishedAction = play_chess_game(game);
        
        free_game(game);
    }

}

int main(int argc, const char * argv[]) {
    
    bool is_console_game = false; // TODO: get from argv[].
    
    // Print initial game message:
    printf(" Chess\n-------\n");
    
    // Get game:
    if (is_console_game) {
        
        // Play game:
        play_console_game();
        printf("Exiting...\n");
    }
    else {
        
        // Initilize Game:
        
        SDL_Init(SDL_INIT_VIDEO);
        
        // Play game:
        
        play_gui_game(NULL);
        
        // Release mem and close SDL:
        SDL_Quit();
    }
    
}
