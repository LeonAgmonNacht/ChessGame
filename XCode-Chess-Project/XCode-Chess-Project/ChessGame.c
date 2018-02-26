//
//  ChessGame.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "ChessGame.h"

// TODO: Doc, add modes ... (mode is console or gui)
// TODO: check for fails

chessGame* init_game(gameSettings* settings) {
    
    // MEM:
    
    chessGame * game = (chessGame *) malloc(sizeof(chessGame));

    // INIT:
    SDL_Renderer* renderer = NULL;
    if (settings->guiMode == GAME_MODE_WITH_GUI) {
        game->boardWindow = init_gui_window();
        renderer = game->boardWindow->window_renderer;
    }
    game->board = init_game_board(settings->guiMode, renderer);
    
    return game;
}


void handle_sdl_event(chessGame* game, SDL_Event* event) {
    
}

gameSettings* get_game_settings() {
    //printf("Specify game settings or type 'start' to begin a game with the current settings:\n");
    //char* currentLine = NULL;
    //while (strcmp(currentLine, "start")) {
    //
    //    LineData* data = parse_line(currentLine);
    //}
    return NULL; // TODO: implement
}
