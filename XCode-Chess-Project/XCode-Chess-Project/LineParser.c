//
//  LineParser.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 25/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "LineParser.h"
#include <stdlib.h>
#include <stdbool.h>


/**
 Parses a string that may contain a command to its command type and params.
 */
LineData* parse_line(char* line) {
    char* commands[] = {GAME_MODE, DIFFICULTY, USER_COLOR, LOAD, DEFAULT, PRINT_SETTINGS, QUIT, START, SAVE_COMMAND, UNDO_COMMAND, RESET_COMMAND, WHITECOLORSTRING_COMMAND, BLACKCOLORSTRING_COMMAND, GAMEMODESTRING_COMMAND, USERCOLORSTRING_COMMAND, DIFFICULTYSTRING_COMMAND};
    char* movesCommands[] = {MOVE_COMMAND, GET_MOVES_COMMAND};
    
    int numCommands = 16;
    int numMoveCommands = 2;
    
    // Detect command:
    
    bool isMoveCommand = false;
    char * lineCommand = NULL;
    
    // Check "regular" commands:
    for(int i = 0; i < numCommands; i++) {
        char* command = commands[i];
        
        if (!strncmp(line, command, strlen(command))) {
            lineCommand = command;
        }
    }
    // Check move commands:
    for(int i = 0; i < numMoveCommands; i++) {
        char* command = commands[i];
        
        if (!strncmp(line, command, strlen(command))) {
            isMoveCommand = true;
            lineCommand = command;
        }
    }
    
    LineData* parsedLine = (LineData*) malloc(sizeof(LineData));
    parsedLine->commandType = lineCommand;
    
    if (lineCommand == NULL) return NULL;
    
    if (!isMoveCommand) {
        
        // Detect args:
        // Skip first token:
        char* token = strtok(line, " ");
        token = strtok(NULL, " "); parsedLine->firstArg = token;
        token = strtok(NULL, " "); parsedLine->secondArg = token;
        
        return parsedLine;
    }
    else {
        // Detect args:
        // Skip first token:
        strtok(line, " ");
        char* firstToken = strtok(NULL, " ");
        char* secondToken = strtok(NULL, " ");
        char* thirdToken = strtok(NULL, " ");
        
        // Preform checks:
        
        if (firstToken == NULL || strlen(firstToken) != strlen("<x,y>") || firstToken[0] != '<' || firstToken[2] != ',' || firstToken[4] != '>') return NULL;
        if (secondToken != NULL && (!strcmp(secondToken, "to") || thirdToken == NULL || strlen(thirdToken) != strlen("<x,y>") || thirdToken[0] != '<' || thirdToken[2] != ',' || thirdToken[4] != '>')) return NULL;
        
        sprintf(parsedLine->firstArg, "%c%c", firstToken[1], '\0');
        sprintf(parsedLine->secondArg, "%c%c", firstToken[3], '\0');
        sprintf(parsedLine->thirdArg, "%c%c", thirdToken[1], '\0');
        sprintf(parsedLine->fourthArg, "%c%c", thirdToken[3], '\0');

        return parsedLine;
    }
}
