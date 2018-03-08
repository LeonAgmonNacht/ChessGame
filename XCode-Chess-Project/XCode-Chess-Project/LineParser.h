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
#define QUIT_COMMAND "quit"

typedef struct LineData {
    char* commandType; // options: GAME_MODE, DIFFICULTY, USER_COLOR, LOAD, DEFAULT, PRINT_SETTINGS, QUIT, START.
    char* firstArg;
    char* secondArg;
    
} LineData;



LineData* parse_line(char* line);

#endif /* LineParser_h */
