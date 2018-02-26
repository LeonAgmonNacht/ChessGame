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

int main(int argc, const char * argv[]) {
    
    // Initilize Game:
    
    SDL_Init(SDL_INIT_VIDEO);
    
    // Print initial game message:
    printf(" Chess\n-------");
    // Game settings states:
    gameSettings* settings = get_game_settings();
    settings = (gameSettings*) malloc(sizeof(gameSettings)); // TODO: delete
    settings->guiMode = GAME_MODE_WITH_GUI; // TODO: delete
    
    chessGame * game = init_game(settings);
    draw_chess_board_according_to_state(game->board, game->boardWindow);
    
    // event handling loop
    bool done = false;
    SDL_Event e;
    while (!done) {
        SDL_WaitEvent(&e);
        handle_sdl_event(game, &e);
    }
    
    SDL_Quit();
    
}
