//
//  GameSettings.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef GameSettings_h
#define GameSettings_h
#include "LineParser.h"
#include <stdio.h>
#include <stdbool.h>
#define BLACKCOLOR 1
#define WHITECOLOR 2
#define GAME_MODE_WITH_GUI 0

// GAME MODES:
#define GAME_MODE_CONSOLE 2
#define GAME_MODE_AI 3
#define GAME_MODE_2_PLAYERS 4

#define INVALID_COMMAND_STRING "ERROR: invalid command\n"
#define MAX_LINE_LENGTH 3000

/**
 A struct to hold the settings needed for a chess game.
 */
typedef struct _game_settings {
    int guiMode; // options: GAME_MODE_WITH_GUI, GAME_MODE_CONSOLE
    int gameMode; // options: GAME_MODE_AI, GAME_MODE_2_PLAYERS
    int difficulty; // options: 1-5
    int userColor; // options: BLACKCOLOR, WHITECOLOR;
} GameSettings;
/**
 Gets a new game settings instance from stdin. In the Doc, this is called the "settings stage".
 If quit is called, a NULL will be returned.
 If a LOAD command was called, isLoad will be set to True,
 and loadPath will have the path to the save game. NULL will be returned.
 */
GameSettings* get_game_settings(void);
/**
 Mallocs and Init a new game settings using the given params
 */
GameSettings* init_game_settings(int diff, int gameMode, int userColor, int guiMode);
/**
 Clons and returns the given settings. NOTE this will malloc a completly new game settings instance
 */
GameSettings* clone_game_settings(GameSettings* settings);
/**
 Prints a string representing the given game settings to the given file
 */
void print_settings_str(FILE* file, GameSettings* settings);
/**
 Get the difficulty represented in the string
 */
int get_difficulty_from_string(const char* difficulty);
#endif /* GameSettings_h */
