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
#include "List.h"
// TODO: consider adding a quit_game method.

chessGame* reset_console_game() {
    // Game settings state:
    gameSettings* settings = get_game_settings();
    
    if (settings == NULL) { // aka quit
        free(settings); // TODO: create costum free method
        return NULL;
    }
    
    settings->guiMode = GAME_MODE_CONSOLE;
    
    chessGame * game = init_game(settings);
    return game;
}

chessGame* reset_gui_game() {
    MainMenu* menu = init_main_menu();
    MainMenuAction* action = wait_for_action(menu);
    if (action == NewGame) {
        SettingsScreen* gameSettingsScreen = init_settings_screen();
        gameSettings* newGameSettings = wait_for_start(gameSettingsScreen);
        chessGame * game = init_game(newGameSettings);
        return game;
    }
}

int main(int argc, const char * argv[]) {
    
    // Initilize Game:

    SDL_Init(SDL_INIT_VIDEO);

    // Print initial game message:
    printf(" Chess\n-------\n");

    // Get game settings:
    chessGame* game = reset_game();

    if (game == NULL) {
        printf("Exiting...\n");
        SDL_Quit();
    }

    // Play game:

    if (game->settings->guiMode == GAME_MODE_WITH_GUI) play_gui_game(game);
    else play_console_game(game);

    // Release mem and close SDL:

    free(game); // TODO: create a free method that frees all sub objects as well.
    SDL_Quit();

  
    
}
