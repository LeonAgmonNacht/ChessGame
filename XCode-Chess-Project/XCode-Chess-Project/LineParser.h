//
//  LineParser.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 25/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef LineParser_h
#define LineParser_h

#include <stdio.h>
#include <string.h>


// Settings:
#define GAME_MODE "game_mode"
#define DIFFICULTY "difficulty"
#define USER_COLOR "user_color"
#define LOAD "load"
#define DEFAULT "default"
#define PRINT_SETTINGS "print_settings"
#define QUIT "quit"
#define START "start"

// Console Game:

#define MOVE_COMMAND "move"
#define GET_MOVES_COMMAND "get_moves"
#define SAVE_COMMAND "save"
#define UNDO_COMMAND "undo"
#define RESET_COMMAND "reset"

/**
 The data that can be found in a parsed command line.
 */
typedef struct LineData {
    char* commandType;
    char* firstArg;
    char* secondArg;
    char* thirdArg;
    char* fourthArg;
} LineData;


/**
 Parses a string that may contain a command to its command type and params.
 */
LineData* parse_line(char* line);

#endif /* LineParser_h */
