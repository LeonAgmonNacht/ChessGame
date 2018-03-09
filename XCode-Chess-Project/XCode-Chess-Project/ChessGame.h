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

typedef struct _chess_game {
    ChessBoard* board;
    GuiChessWindow* boardWindow; // This pointer will be null for console mode games
    GameSettings* settings;
    bool currentPlayerWhite;
} ChessGame;

typedef enum {
    GameFinishedActionMainMenu,
    GameFinishedActionQuit,
    GameFinishedActionReset,
} GameFinishedStatusEnum;

GameSettings* get_game_settings(void);
ChessGame* init_game(GameSettings* settings);
void free_game(ChessGame* game);
void handle_sdl_event(ChessGame* game, SDL_Event* event);
GameFinishedStatusEnum play_chess_game(ChessGame* game);

GameSettings* init_game_settings(int diff, int gameMode, int userColor, int guiMode);
GameSettings* clone_game_settings(GameSettings* settings);

/**
 Loads a game from the given file path
 */
ChessGame* load_from_file(char* filePath);
/**
 Return the path to the saved game slot slot
 */
char* get_saved_game_path(int slot);

ChessGame* load_game_from_slot_index(int slot, int guiMode);

void save_game_to_slot_index(int slot, ChessGame* game);

#endif /* ChessGame_h */
