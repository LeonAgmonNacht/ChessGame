//
//  ChessGame.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef ChessGame_h
#define ChessGame_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "GUIChessWindow.h"
#include "GameSettings.h"

#define LOAD_GAME_FILE_NAME_FORMAT "./Saved-Games/slot_%d.txt"
/**
 A struct representing a chess game. Including its data, settings, UI if exists and more.
 */
typedef struct _chess_game {
    ChessBoard* board;
    GuiChessWindow* boardWindow; // This pointer will be null for console mode games
    GameSettings* settings;
    bool currentPlayerWhite;
    bool saved; // True iff the game was saved, and no move was preformed afterwards.
} ChessGame;

/**
 Specifies the possible outcomes of a game.
 */
typedef enum {
    GameFinishedActionMainMenu,
    GameFinishedActionQuit,
    GameFinishedActionReset,
    GameFinishedActionUndetermined,
    GameFinishedActionDraw,
    GameFinishedActionMate,
    GameFinishedActionCheck
} GameFinishedStatusEnum;


/**
 insert a game to history

 @param game game to insert
 */
void insert_game_to_history(ChessGame* game);


/**
 pop last game from memory of games

 @param game game to pop to
 @return true if poped, false if no games saved in history
 */
bool pop_last_game_from_memory(ChessGame* game);
/**
 Mallocs and inits a new game with the given game settings and boardData. If the board is NULL a board representing a new game will be set
 */
ChessGame* init_game(GameSettings* settings, ChessBoard* board);

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
ChessGame* load_from_file(char* filePath, int guiMode);
/**
 Saves a game from the given file path. True iff saved.
 */
bool save_game_to_file(FILE* file, ChessGame* game);
/**
 Return the path to the saved game slot slot
 */
char* get_saved_game_path(int slot);
/**
 Loads a pre-saved game from the given slot. If the game does not exist, returns NULL
 */
ChessGame* load_game_from_slot_index(int slot, int guiMode);
/**
 Saves the given game to the given slot index. True iff saved.
 */
bool save_game_to_slot_index(int slot, ChessGame* game);

#endif /* ChessGame_h */
