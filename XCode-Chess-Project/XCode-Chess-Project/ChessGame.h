//
//  ChessGame.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef ChessGame_h
#define ChessGame_h

#define LOAD_GAME_FILE_NAME_FORMAT "./Saved-Games/slot_%d.txt"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "GUIChessWindow.h"
#include "GameSettings.h"

/**
 A struct representing a chess game. Including its data, settings, UI if exists and more.
 */
typedef struct _chess_game {
    ChessBoard* board;
    GuiChessWindow* boardWindow; // This pointer will be null for console mode games
    GameSettings* settings;
    bool currentPlayerWhite;
} ChessGame;

/**
 Specifies the possible outcomes of a game.
 */
typedef enum {
    GameFinishedActionMainMenu,
    GameFinishedActionQuit,
    GameFinishedActionReset,
    GameFinishedActionUndetermined,
    GameFinishedActionDrawOrMate
} GameFinishedStatusEnum;

/**
 Mallocs and inits a new game with the given game settings.
 */
ChessGame* init_game(GameSettings* settings);
/**
 Frees all resources of the given game.
 NOTE this will also free the gui, if exists and the settings.
 */
void free_game(ChessGame* game);
/**
 Play the given game (gui/console mode) and return once it is done. Return with the cause.
 */
GameFinishedStatusEnum play_chess_game(ChessGame* game);
/**
 Loads a game from the given file path
 */
ChessGame* load_from_file(char* filePath);
/**
 Saves a game from the given file path
 */
void save_game_to_file(FILE* file, ChessGame* game);
/**
 Return the path to the saved game slot slot
 */
char* get_saved_game_path(int slot);
/**
 Loads a pre-saved game from the given slot. If the game does not exist, returns NULL
 */
ChessGame* load_game_from_slot_index(int slot, int guiMode);
/**
 Saves the given game to the given slot index.
 */
void save_game_to_slot_index(int slot, ChessGame* game);

#endif /* ChessGame_h */
