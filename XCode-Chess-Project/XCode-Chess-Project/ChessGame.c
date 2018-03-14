//
//  ChessGame.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessGame.h"
#include "LoadGameScreen.h"
#include "ChessGameConsoleUtils.h"
#include "ChessGameGuiUtils.h"

/**
 Mallocs and inits a new game with the given game settings.
 */
ChessGame* init_game(GameSettings* settings) {
    
    // MEM:
    
    ChessGame * game = (ChessGame *) malloc(sizeof(ChessGame));
    
    // INIT:
    SDL_Renderer* renderer = NULL;
    if (settings->guiMode == GAME_MODE_WITH_GUI) {
        game->boardWindow = init_gui_window();
        renderer = game->boardWindow->windowRenderer;
    }
    game->board = init_game_board(settings->guiMode, renderer);
    game->settings = settings;
    game->currentPlayerWhite = settings->userColor == WHITECOLOR;
    return game;
}

/**
 Frees all resources of the given game.
 NOTE this will also free the gui, if exists and the settings.
 */
void free_game(ChessGame* game) {
    free_chess_board(game->board);
    if (game->boardWindow != NULL) free_gui_window(game->boardWindow);
    free(game->settings);
    free(game);
}

/**
 Play the given game (gui/console mode) and return once it is done. Return with the cause.
 */
GameFinishedStatusEnum play_chess_game(ChessGame* game) {
    if (game->settings->guiMode == GAME_MODE_WITH_GUI) {
        draw_chess_board_according_to_state(game->board, game->boardWindow);
        return play_gui_game(game);
    }
    else {
        return play_console_game(game);
    }
    return GameFinishedActionReset;
}

// MARK: Utils:

/**
 Loads a game from the given file path
 */
ChessGame* load_from_file(char* filePath) {
    // TODO: Implement.
    return NULL;
}
/**
 Saves a game from the given file path
 */
void save_game_to_file(FILE* file, ChessGame* game) {
    // TODO: Implement.
}

/**
 Return the path to the saved game slot slot
 */
char* get_saved_game_path(int slot) {
    char* path = (char*)malloc(strlen(LOAD_GAME_FILE_NAME_FORMAT)-1); // -1 because %d is a single char after format
    sprintf(path, LOAD_GAME_FILE_NAME_FORMAT, slot);
    return path;
}
/**
 Loads a pre-saved game from the given slot. If the game does not exist, returns NULL
 */
ChessGame* load_game_from_slot_index(int slot, int guiMode) {
    // TODO: implement
    return NULL;
}
/**
 Saves the given game to the given slot index.
 */
void save_game_to_slot_index(int slot, ChessGame* game) {
    // TODO: Implement.
}
