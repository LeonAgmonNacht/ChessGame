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

#define GAME_MODE "game_mode"
#define DIFFICULTY "difficulty"
#define USER_COLOR "user_color"
#define LOAD "load"
#define DEFAULT "default"
#define PRINT_SETTINGS "print_settings"
#define QUIT "quit"
#define START "start"

typedef struct lineData {
    char* commandType; // options: GAME_MODE, DIFFICULTY, USER_COLOR, LOAD, DEFAULT, PRINT_SETTINGS, QUIT, START.
    char* firstArg;
    char* secondArg;
    
} lineData;



lineData* parse_line(char* line);

#endif /* LineParser_h */
