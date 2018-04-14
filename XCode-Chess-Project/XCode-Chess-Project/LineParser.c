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
 Warning this will change the data in line.
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
        
        if ((strncmp(line, command, strlen(command)) == 0) && (line[strlen(command)] == '\0' || line[strlen(command)] == ' ')) {
            lineCommand = command;
        }
    }
    // Check move commands:
    for(int i = 0; i < numMoveCommands; i++) {
        char* command = movesCommands[i];
        
        if ((strncmp(line, command, strlen(command)) == 0) && (line[strlen(command)] == '\0' || line[strlen(command)] == ' ')) {
            isMoveCommand = true;
            lineCommand = command;
        }
    }
    
    LineData* parsedLine = (LineData*) malloc(sizeof(LineData));
    parsedLine->commandType = lineCommand;
    
    if (lineCommand == NULL) return NULL;
    
    parsedLine->firstArg = NULL;
    parsedLine->secondArg = NULL;
    parsedLine->thirdArg = NULL;
    parsedLine->fourthArg = NULL;
    
    if (!isMoveCommand) {
        
        // Detect args:
        // Skip first token:
        char* token = strtok(line, " ");
        token = strtok(NULL, " ");
        if (token != NULL && strlen(token) != 0) {
            parsedLine->firstArg = (char*)malloc(strlen(token)+1);
            strcpy(parsedLine->firstArg, token);
        } else parsedLine->firstArg = NULL;
        token = strtok(NULL, " ");
        if (token != NULL && strlen(token) != 0) {
            parsedLine->secondArg = (char*)malloc(strlen(token)+1);
            strcpy(parsedLine->secondArg, token);
        }
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
        
        if (firstToken == NULL || strlen(firstToken) != strlen("<x,y>") || firstToken[2] != ','){
            free(parsedLine);
            return NULL;
        }
        if (secondToken != NULL && (strcmp(secondToken, "to") !=0 || thirdToken == NULL || strlen(thirdToken) != strlen("<x,y>") ||thirdToken[2] != ',')){
            free(parsedLine);
            return NULL;
            
        }
        
        // Malloc
        parsedLine->firstArg = (char*)malloc(2);
        parsedLine->secondArg = (char*)malloc(2);
        parsedLine->thirdArg = (char*)malloc(2);
        parsedLine->fourthArg = (char*)malloc(2);
        
        parsedLine->firstArg[0] = firstToken[1]; parsedLine->firstArg[1] = '\0';
        parsedLine->secondArg[0] = firstToken[3]; parsedLine->secondArg[1] = '\0';
        
        if (thirdToken != NULL) {
            parsedLine->thirdArg[0] = thirdToken[1]; parsedLine->thirdArg[1] = '\0';
            parsedLine->fourthArg[0] = thirdToken[3]; parsedLine->fourthArg[1] = '\0';
        }

        return parsedLine;
    }
}
/**
 Frees resources used by data
 */
void free_line_data(LineData* data) {
    if (data->firstArg != NULL) free(data->firstArg);
    if (data->secondArg != NULL) free(data->secondArg);
    if (data->thirdArg != NULL) free(data->thirdArg);
    if (data->fourthArg != NULL) free(data->fourthArg);
    free(data);
    
}
