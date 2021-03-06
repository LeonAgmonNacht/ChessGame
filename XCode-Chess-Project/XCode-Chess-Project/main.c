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

#define CONSOLE_MODE_ARG_STRING "-c"

/**
 Asks the user in stdin for the game settings and returns the entered ones.
 if defaultGameSettings is not NULL uses it as a param to get_game_settings
 */
ChessGame* reset_console_game(GameSettings* defaultGameSettings) {
    // Game settings state:
    bool isLoad = false;
    char* loadPath = (char*)malloc(MAX_LINE_LENGTH+1);
    GameSettings* settings = get_game_settings(&isLoad, loadPath, defaultGameSettings);
    if (isLoad == true) {
        ChessGame* game = load_from_file(loadPath, GAME_MODE_CONSOLE);
        if (game == NULL) {
            printf("Error: File doesn’t exist or cannot be opened\n");
            ChessGame* game = reset_console_game(settings);
            return game;
        }
        return game;
    }
    
    if (settings == NULL) { // aka quit
        return NULL;
    }
    
    ChessGame * game = init_game(settings, NULL);
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
        ChessGame * game = init_game(newGameSettings, NULL);
        return game;
    }
    else if (action == MenuActionLoadGame) { // User wishs to load a game, present the load screen
        LoadGameScreen* loadScreen = init_load_game_screen(true); // true because we are loading from a slot, and not saving to one.
        int slotIndex = wait_for_slot_choice(loadScreen, true); // true because we are loading from a slot, and not saving to one.
        free_load_game_screen(loadScreen);
        if (slotIndex == -1) { // Back
            ChessGame* game = reset_gui_game(); // Restart proccess
            return game;
        }
        ChessGame* game = load_game_from_slot_index(slotIndex, GAME_MODE_WITH_GUI);
        return game;
    }
    else { // Action is Quit
        
    }
    
    return NULL;
}

/**
 Play a gui game with the given settings, if NULL reset_gui_game function will be called
 */
void main_play_gui_game(GameSettings* settings) {
    ChessGame* game;
    if (settings == NULL) { game = reset_gui_game();}
    else {game = init_game(settings, NULL);}
    
    if (game != NULL) {
        GameFinishedStatusEnum finishedAction = play_chess_game(game);
        if (finishedAction == GameFinishedActionMainMenu) {
            free_game(game);
            main_play_gui_game(NULL);
            
        }
        else if (finishedAction == GameFinishedActionReset) {
            GameSettings* settings = clone_game_settings(game->settings);
            free_game(game);
            main_play_gui_game(settings);
        }
        else { // Finished action is quit
        free_game(game);
        }
    }
}
/**
 Play a console game with the given settings, if NULL reset_console_game function will be called
 */
void main_play_console_game(GameSettings* settings) {
    // Get game settings:
    ChessGame* game;
    if (settings == NULL) { game = reset_console_game(NULL);}
    else { game = init_game(settings, NULL); }
    
    if (game != NULL) {
        printf("Starting game...\n");
        GameFinishedStatusEnum finishedAction = play_chess_game(game);
        if (finishedAction == GameFinishedActionMainMenu) { // Cant get here
            printf("Shouldn't get here");
        }
        else if (finishedAction == GameFinishedActionReset) {
            
            free_game(game);
            printf("Restarting...\n");
            main_play_console_game(NULL);
        }
        else if (finishedAction == GameFinishedActionDraw || finishedAction == GameFinishedActionMate) {
            free(game);
            return;
        }
        else { // Finished action is quit
            free_game(game);
        }
    }

}

int main(int argc, const char * argv[]) {
    
    // One liner to determine if we need to use the default (console) or read mode from argv
    bool is_console_game = argc == 1 ? true : strcmp(argv[1], CONSOLE_MODE_ARG_STRING) == 0;
    
    // Get game:
    if (is_console_game) {
        
        // Play game:
        // Print initial game message:
        printf(" Chess\n-------\n");
        main_play_console_game(NULL);
        printf("Exiting...\n");
    }
    else {
        
        // Initilize Game:
        
        SDL_Init(SDL_INIT_VIDEO);
        
        // Play game:
        
        main_play_gui_game(NULL);
        
        // Release mem and close SDL:
        SDL_Quit();
    }
    
}
