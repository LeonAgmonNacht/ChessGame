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
    
    char * lineCommand = NULL;
    for(int i = 0; i < numCommands; i++) {
        char* command = commands[i];
        
        if (strncmp(line, command, strlen(command))) {
            lineCommand = command;
        }
    }
    if (lineCommand == NULL) return NULL;
    
    // Detect args:
    LineData* parsedLine = (LineData*) malloc(sizeof(LineData));
    parsedLine->commandType = lineCommand;
    
    // Skip first token:
    char* token = strtok(line, " ");
    token = strtok(token, " "); parsedLine->firstArg = token;
    token = strtok(token, " "); parsedLine->secondArg = token;
    
    return NULL;
}
