//
//  main.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "ChessGame.h"

// TODO: consider adding a quit_game method.

chessGame* reset_game() {
    // Game settings state:
    gameSettings* settings = get_game_settings();
    
    if (settings == NULL) { // aka quit
        free(settings); // TODO: create costum free method
        return NULL;
    }
    
    settings->guiMode = GAME_MODE_WITH_GUI; // TODO: get from argv[].
    
    chessGame * game = init_game(settings);
    return game;
}

int main(int argc, const char * argv[]) {
    
    // Initilize Game:
    
    SDL_Init(SDL_INIT_VIDEO);
    
    // Print initial game message:
    printf(" Chess\n-------\n");
    
    chessGame* game = reset_game();
    
    if (game == NULL) {
        printf("Exiting...\n");
        SDL_Quit();
        return 0;
    }
    
    draw_chess_board_according_to_state(game->board, game->boardWindow);
    
    // event handling loop
    bool done = false;
    SDL_Event e;
    while (!done) {
        SDL_WaitEvent(&e);
        handle_sdl_event(game, &e);
    }
    free(game); // TODO: create a free method that frees all sub objects as well.
    SDL_Quit();
    
}
