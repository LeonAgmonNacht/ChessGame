//
//  ChessGame.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessGame.h"

// TODO: Docs
ChessGame* init_game(GameSettings* settings) {
    
    // MEM:
    
    ChessGame * game = (ChessGame *) malloc(sizeof(ChessGame));
    
    // INIT:
    SDL_Renderer* renderer = NULL;
    if (settings->guiMode == GAME_MODE_WITH_GUI) {
        game->boardWindow = init_gui_window();
        renderer = game->boardWindow->windowRenderer;
    }
    game->board = init_game_board(settings->guiMode, renderer);
    game->settings = settings;
    game->currentPlayerWhite = settings->userColor == WHITECOLOR;
    return game;
}

void free_game(ChessGame* game) {
    free_chess_board(game->board);
    if (game->boardWindow != NULL) free_gui_window(game->boardWindow);
    free(game->settings);
    free(game);
}

/**
 Handle a move action for a game, if this is a gui game, the gui will be re-rendered
 The move is represented by start cell and destination cell.
 */
void _handle_move_event(Cell* startCell, Cell* destCell) {
    
}

// TODO: when implmented fully, check if should move to ChessBoard
bool _verify_valid_start_pos_move(ChessGame* game, Cell* cell) {
    if (game->board->boardData[cell->row][cell->column] == NULL) return false;
    if (game->currentPlayerWhite != game->board->boardData[cell->row][cell->column]->isWhite) return false;
    return true;
}

bool _verify_valid_end_pos_move(ChessGame* game, Cell* startCell, Cell* destCell) {
    if (game->board->boardData[destCell->row][destCell->column] == NULL) return true;
    // TODO: add checks, e.g. move is in get_possible_moves
    // TODO: also check can be eaten.
    return true;
}

/**
 Preforms a move, updates the UI/Console if needed.
 */
void _preform_chess_game_move(ChessGame*game, Cell* startCell, Cell* destCell) {
    // TODO: remember if eats to free piece.
    preform_board_move(game->board, startCell, destCell);
    if (game->settings->guiMode == GAME_MODE_WITH_GUI) {
        draw_chess_board_according_to_state(game->board, game->boardWindow);
    }
    // TODO: add UI
    
    game->currentPlayerWhite = !game->currentPlayerWhite;
}

/**
 Play a game which has gui type gui game until it is finished. Return the reason.
 NOTE: a load/save/undo/move_piece are handled internally.
 */
GameFinishedStatusEnum _play_gui_game(ChessGame* game) {
    
    Cell* cell = NULL; // Will be used to store the first-cell-clicked by the user, next cell-click will cause a move.
    bool gameHasEnded = false; // true if the game has ended -> disables moving the pieces but allowing the user to choose his next action.
    while (true) {
        ChessWindowAction* action = wait_for_move_or_action(game->boardWindow);
        
        // Outer responsibillity:
        if (action->actionType==QuitClicked) return GameFinishedActionQuit;
        else if (action->actionType == RestartClicked) return GameFinishedActionReset;
        else if (action->actionType == MainMenuClicked) return GameFinishedActionMainMenu;
        
        // Inner responsibillity:
        // TODO: Implement
//        else if (action->actionType == LoadClicked)
//        else if (action->actionType == SaveClicked)
//        else if (action->actionType == UndoClicked)
        // Move handling:
        else if (action->actionType == BoardMove && !gameHasEnded) {
            if (cell == NULL) {
                if (!_verify_valid_start_pos_move(game, action->cellClicked)) continue;
                cell = action->cellClicked;
                action->cellClicked = NULL; // So it won't be freed
            }
            else {
                if (!_verify_valid_end_pos_move(game, cell, action->cellClicked)) continue;
                _preform_chess_game_move(game, cell, action->cellClicked);
                gameHasEnded = check_game_ended(game->board);
                cell = NULL;
                free(cell);
            }
        }
        free_window_action(action);
    }
    return GameFinishedActionQuit;
}
                    


GameFinishedStatusEnum play_chess_game(ChessGame* game) {
    if (game->settings->guiMode == GAME_MODE_WITH_GUI) {
        draw_chess_board_according_to_state(game->board, game->boardWindow);
        return _play_gui_game(game);
    }
    return GameFinishedActionReset;
}

// MARK: Get Settings:

GameSettings* init_game_settings(int diff, int gameMode, int userColor, int guiMode) {
    GameSettings* settings = (GameSettings*)malloc(sizeof(GameSettings));
    settings->difficulty = diff;
    settings->gameMode = gameMode;
    settings->guiMode = guiMode;
    settings->userColor = userColor;
    return settings;
}

GameSettings* clone_game_settings(GameSettings* settings) {
    return init_game_settings(settings->difficulty, settings->gameMode, settings->userColor, settings->guiMode);
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

void _set_to_default(GameSettings* settings) {
    settings->gameMode = GAME_MODE_AI;
    settings->difficulty = 2; // CONSIDER moving from 2 to an enum sort of thing.
    settings->userColor = WHITECOLOR;
    settings->guiMode=GAME_MODE_CONSOLE;
}

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

// MARK: Utils:

/**
 Loads a game from the given file path
 */
ChessGame* load_from_file(char* filePath) {
    // TODO: Implement.
    return NULL;
}
/**
 Return the path to the saved game slot slot
 */
char* get_saved_game_path(int slot) {
    char* path = (char*)malloc(strlen(LOAD_GAME_FILE_NAME_FORMAT)-1); // -1 because %d is a single char after format
    sprintf(path, LOAD_GAME_FILE_NAME_FORMAT, slot);
    return path;
}

