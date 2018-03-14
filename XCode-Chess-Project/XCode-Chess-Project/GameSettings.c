//
//  GameSettings.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "GameSettings.h"
#include <stdlib.h>
// DIFS MODES:
#define AMATEUR_STRING "amateur";
#define EASY_STRING "easy";
#define MODERATE_STRING "moderate";
#define HARD_STRING "hard";
#define EXPERT_STRING "expert";
#define DEFAULT_DIFFICULTY_LEVEL 2;
/**
 Mallocs and Init a new game settings using the given params
 */
GameSettings* init_game_settings(int diff, int gameMode, int userColor, int guiMode) {
    GameSettings* settings = (GameSettings*)malloc(sizeof(GameSettings));
    settings->difficulty = diff;
    settings->gameMode = gameMode;
    settings->guiMode = guiMode;
    settings->userColor = userColor;
    return settings;
}
/**
 Clons and returns the given settings. NOTE this will malloc a completly new game settings instance.
 */
GameSettings* clone_game_settings(GameSettings* settings) {
    return init_game_settings(settings->difficulty, settings->gameMode, settings->userColor, settings->guiMode);
}
/**
 Returns a string representing the given difficulty.
 */
char* _get_difficulty_string(int diff) {
    
    switch (diff) {
        case 1: return AMATEUR_STRING;
        case 2: return EASY_STRING;
        case 3: return MODERATE_STRING;
        case 4: return HARD_STRING;
        case 5: return EXPERT_STRING;
        default:
            break;
    }
    return NULL;
}
/**
 Sets the given settings to all default values
 */
void _set_to_default(GameSettings* settings) {
    settings->gameMode = GAME_MODE_AI;
    settings->difficulty = DEFAULT_DIFFICULTY_LEVEL;
    settings->userColor = WHITECOLOR;
    settings->guiMode=GAME_MODE_CONSOLE;
}
/**
 Given a parsed command, apply it to the settings.
 */
void _apply_command_to_settings(GameSettings* settings, LineData* data) {
    
    // Checking if data is DIFFICULTY:
    
    if (!strcmp(data->commandType, DIFFICULTY)) {
        int diff = atoi(data->firstArg);
        if (diff > 5 || diff < 1) {// 0 is invalid int
            printf("Wrong difficulty level. The value should be between 1 to 5\n");
        }
        else {
            settings->difficulty = diff;
            printf("Difficulty level is set to %s\n", _get_difficulty_string(diff));
        }
    }
    
    // Checking if data is GAME_MODE:
    
    else if (!strcmp(data->commandType, GAME_MODE)) {
        int game_mode = atoi(data->firstArg);
        if (game_mode == 2 || game_mode == 1) {
            settings->gameMode = game_mode == 2 ? GAME_MODE_2_PLAYERS : GAME_MODE_AI;
            printf( "Game mode is set to %s\n", (game_mode == 2 ? "2-player" : "1-player"));
        }
        else {
            printf("Wrong game mode\n");
        }
    }
    
    // Checking if data is USER_COLOR:
    
    else if (!strcmp(data->commandType, USER_COLOR)) {
        
        if (settings->gameMode != GAME_MODE_AI) {
            printf(INVALID_COMMAND_STRING);
        }
        else {
            int color = atoi(data->firstArg);
            if (color == 0 || color == 1) {
                settings->userColor = color == 0 ? BLACKCOLOR : WHITECOLOR;
                printf("User color is set to %s\n", color == 0 ? "black" : "white");
            }
            else {
                printf("Wrong user color. The value should be 0 or 1\n");
            }
        }
    }
    
    // Checking if data is LOAD:
    
    // TODO: implement!!!
    
    // Checking if data is DEFAULT:
    
    else if (!strcmp(data->commandType, DEFAULT)) {
        printf("All settings reset to default\n");
        _set_to_default(settings);
    }
    
    // Checking if data is PRINT_SETTINGS
    else if (!strcmp(data->commandType, PRINT_SETTINGS)) {
        if (settings->gameMode == GAME_MODE_2_PLAYERS) printf("SETTINGS:\nGAME_MODE: 2-player\n");
        else printf("SETTINGS:\nGAME_MODE: 1-player\nDIFFICULTY: %s\nUSER_COLOR: %s\n",
                    _get_difficulty_string(settings->difficulty),
                    settings->userColor == WHITECOLOR ? "white" : "black");
    }
}

/**
 Gets a new game settings instance from stdin. In the Doc, this is called the "settings stage".
 If quit is called, a NULL will be returned.
 */
GameSettings* get_game_settings() {
    printf("Specify game settings or type 'start' to begin a game with the current settings:\n");
    char* currentLine = (char*)malloc(MAX_LINE_LENGTH+1);
    GameSettings* settings = (GameSettings*)malloc(sizeof(GameSettings));
    
    // SET DEFAULT:
    _set_to_default(settings);
    
    // GET SETTINGS:
    
    while ((fgets(currentLine, MAX_LINE_LENGTH, stdin)!= NULL)) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        LineData* data = parse_line(currentLine);
        if (data == NULL) {
            printf(INVALID_COMMAND_STRING);
            continue;
        }
        else if (!(strcmp(currentLine, START) && strcmp(currentLine, QUIT))) {
            break;
        }
        else {
            _apply_command_to_settings(settings, data);
        }
        
        free(data); // TODO: if needed, create costum free method
    }
    
    if (!strcmp(currentLine, QUIT)) return NULL;
    
    // TODO: add to docs, if quit is entered, NULL is returned.
    
    free(currentLine);
    return settings;
}
