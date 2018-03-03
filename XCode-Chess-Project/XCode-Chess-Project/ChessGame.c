//
//  ChessGame.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessGame.h"

// TODO: Doc, add modes ... (mode is console or gui)
// TODO: check for fails

chessGame* init_game(gameSettings* settings) {
    
    // MEM:
    
    chessGame * game = (chessGame *) malloc(sizeof(chessGame));
    
    // INIT:
    SDL_Renderer* renderer = NULL;
    if (settings->guiMode == GAME_MODE_WITH_GUI) {
        game->boardWindow = init_gui_window();
        renderer = game->boardWindow->window_renderer;
    }
    game->board = init_game_board(settings->guiMode, renderer);
    game->settings = settings;
    return game;
}


void handle_sdl_event(chessGame* game, SDL_Event* event) {
    
}

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

void _set_to_default(gameSettings* settings) {
    settings->gameMode = GAME_MODE_AI;
    settings->difficulty = 2; // CONSIDER moving from 2 to an enum sort of thing.
    settings->userColor = WHITECOLOR;
}

void _apply_command_to_settings(gameSettings* settings, lineData* data) {
    
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
            printf("ERROR: invalid command\n");
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


gameSettings* get_game_settings() {
    printf("Specify game settings or type 'start' to begin a game with the current settings:\n");
    char* currentLine = (char*)malloc(MAX_LINE_LENGTH+1);
    gameSettings* settings = (gameSettings*)malloc(sizeof(gameSettings));
    
    // SET DEFAULT:
    _set_to_default(settings);
    
    // GET SETTINGS:
    
    while ((fgets(currentLine, MAX_LINE_LENGTH, stdin)!= NULL)) {
        currentLine[strcspn(currentLine, "\n")] = '\0';
        lineData* data = parse_line(currentLine);
        if (data == NULL) {
            printf("ERROR: invalid command\n");
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
