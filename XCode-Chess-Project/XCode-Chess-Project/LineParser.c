//
//  LineParser.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 25/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "LineParser.h"

LineData* parse_line(char* line) {
    char* commands[] = {GAME_MODE, DIFFICULTY, USER_COLOR, LOAD, DEFAULT, PRINT_SETTINGS, QUIT, START};
    int numCommands = 8;
    
    
    // Detect command:
    
    char * lineCommand;
    for(int i = 0; i < numCommands; i++) {
        char* command = commands[i];
        // NOTE: might need to add back-salsh-0 to commands...
        if (strncpy(line, command, strlen(command))) {
            lineCommand = command;
        }
    }
    
    // Detect args:
    return NULL;
}
