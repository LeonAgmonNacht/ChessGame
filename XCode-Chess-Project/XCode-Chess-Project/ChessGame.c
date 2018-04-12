//
//  ChessGame.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessGame.h"
#include "LoadGameScreen.h"
#include "ChessGameConsoleUtils.h"
#include "ChessGameGuiUtils.h"
#define HISTORY_SIZE 6
List* savedGames = NULL;


void _free_game_from_history(void* gameToFree){
    SavedGame* game = gameToFree;
    free_chess_board(game->game->board);
    free(game->game->settings);
    free(game->game);
    free(game);
}
SavedGame* _copy_game_for_history(SavedGame* game){
   SavedGame* copiedGame=malloc(sizeof(SavedGame));
    copiedGame->game = malloc(sizeof(ChessGame));
    copiedGame->game->board = copy_board(game->game->board);
    copiedGame->game->currentPlayerWhite = game->game->currentPlayerWhite;
    copiedGame->game->settings = malloc(sizeof(GameSettings));
    *(copiedGame->game->settings) = *(game->game->settings);
    copiedGame->game->saved = false;
    
    copiedGame->game->boardWindow = game->game->boardWindow;
    copiedGame->move = game->move;
    return copiedGame;
}

void insert_game_to_history(SavedGame* savedGame){
    if(get_items_count(savedGames)== HISTORY_SIZE){
        SavedGame* leastRecentGameSaved = get_element(savedGames, 0);
        _free_game_from_history(leastRecentGameSaved);
       
        delete_item(savedGames, 0);
    }
    
    insert_item(savedGames, _copy_game_for_history(savedGame));
    
}

bool pop_last_game_from_memory(SavedGame* game){
    SavedGame* lastGame = NULL;
    const int lastGameIndex = (int)get_items_count(savedGames) - 1;
    if(lastGameIndex>=0){
        lastGame = get_last_element(savedGames);
        delete_item(savedGames, lastGameIndex);
        free(game->game->settings);
        free_chess_board(game->game->board);
        game->game->settings = malloc(sizeof(GameSettings));
        *(game->game->settings) = *(lastGame->game->settings);
        game->game->board = copy_board(lastGame->game->board);
         game->game->boardWindow = lastGame->game->boardWindow;
         game->game->currentPlayerWhite = lastGame->game->currentPlayerWhite;
        game->game->saved = false;
        game->move = lastGame->move;
        _free_game_from_history(lastGame);
        
       
    
        return true;
    }
    else{
        return false;
    }
    
}
/**
 Mallocs and inits a new game with the given game settings and boardData. If the board is NULL a board representing a new game will be set
 */
ChessGame* init_game(GameSettings* settings, ChessBoard* board) {
    
    // MEM:
    
    ChessGame * game = (ChessGame *) malloc(sizeof(ChessGame));
    
    // INIT:
    if (settings->guiMode == GAME_MODE_WITH_GUI) game->boardWindow = init_gui_window();
    else game->boardWindow = NULL;
    if (board == NULL) game->board = init_game_board();
    else game->board = board;
    
    game->settings = settings;
    game->currentPlayerWhite = settings->userColor == WHITECOLOR;
    game->saved = true;
    if(savedGames==NULL){
        savedGames = init_list_without_copy(HISTORY_SIZE, _free_game_from_history);
    }
    return game;
}

/**
 Frees all resources of the given game.
 NOTE this will also free the gui, if exists and the settings.
 */
void free_game(ChessGame* game) {
    free_chess_board(game->board);
    if (game->boardWindow != NULL) free_gui_window(game->boardWindow);
    free(game->settings);
    free(game);
    free_list(savedGames);
    savedGames = NULL;
}

/**
 Play the given game (gui/console mode) and return once it is done. Return with the cause.
 */
GameFinishedStatusEnum play_chess_game(ChessGame* game) {
    if (game->settings->guiMode == GAME_MODE_WITH_GUI) {
        draw_chess_board_according_to_state(game->board, game->boardWindow, NULL);
        return play_gui_game(game);
    }
    else {
        return play_console_game(game);
    }
    return GameFinishedActionReset;
}
/**
 Frees the existing board and sets the new one
 */
void _set_chess_board(ChessGame* game, ChessBoard* newBoard) {
    free_chess_board(game->board);
    game->board = newBoard;
}

// MARK: Utils:

/**
 Loads a game from the given file path
 */
ChessGame* load_from_file(char* filePath, int guiMode) {
    
    char* currentLine = (char*)malloc(MAX_LINE_LENGTH);
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {free(currentLine); return NULL;}
    
    int userColor = -1, difficulty = -1, gameMode = -1;
    bool validData = true, currentPlayerWhite = false;
    
    if (fgets(currentLine, MAX_LINE_LENGTH, file)== NULL) {fclose(file);free(currentLine); return NULL;}
    currentLine[strcspn(currentLine, "\n")] = '\0';
    if (strcmp(currentLine, WHITE_COLOR_STR) == 0) currentPlayerWhite = true;
    else if (strcmp(currentLine, BLACK_COLOR_STR) == 0) currentPlayerWhite = false;
    else validData = false;
    // skip SETTINGS:
    if (fgets(currentLine, MAX_LINE_LENGTH, file)== NULL) {fclose(file);free(currentLine); return NULL;}
    if (fgets(currentLine, MAX_LINE_LENGTH, file)== NULL) {fclose(file);free(currentLine); return NULL;}
    currentLine[strcspn(currentLine, "\n")] = '\0';
    LineData* gameModeData = parse_line(currentLine);
    if (gameModeData->commandType != GAMEMODESTRING_COMMAND) validData = false;
    if (strcmp(gameModeData->firstArg, "1-player") == 0) gameMode = GAME_MODE_AI;
    else if (strcmp(gameModeData->firstArg, "2-player") == 0) gameMode = GAME_MODE_2_PLAYERS;
    else validData = false;
    free(gameModeData);
    if (gameMode == GAME_MODE_AI) {
        if (fgets(currentLine, MAX_LINE_LENGTH, file)== NULL) {fclose(file);free(currentLine); return NULL;}
        currentLine[strcspn(currentLine, "\n")] = '\0';
        LineData* difficultyData = parse_line(currentLine);
        if (fgets(currentLine, MAX_LINE_LENGTH, file)== NULL) {fclose(file);free(currentLine); return NULL;}
        currentLine[strcspn(currentLine, "\n")] = '\0';
        LineData* userColorData = parse_line(currentLine);
        
        if (difficultyData->commandType == DIFFICULTYSTRING_COMMAND) {
            difficulty = get_difficulty_from_string(difficultyData->firstArg);
        }
        else validData = false;
        if (userColorData->commandType == USERCOLORSTRING_COMMAND) {
            
            if (strcmp(userColorData->firstArg, WHITE_COLOR_STR) == 0) userColor = WHITECOLOR;
            else if (strcmp(userColorData->firstArg, BLACK_COLOR_STR) == 0) userColor = BLACKCOLOR;
            else validData = false;
        }
        free(difficultyData);
        free(userColorData);
    }
    else {
        userColor = WHITECOLOR; // Default
        difficulty = 1; // Default
    }
    
    free(currentLine);
    
    
    if (!validData) return NULL;
    
    GameSettings* settings = init_game_settings(difficulty,
                                                gameMode,
                                                userColor,
                                                guiMode);
    
    ChessBoard* board = load_board_from_file(file);
    ChessGame* game = init_game(settings, board);
    if (game == NULL) return NULL;
    game->currentPlayerWhite = currentPlayerWhite;
    fclose(file);
    return game;
}
/**
 Saves a game from the given file path. True iff saved.
 */
bool save_game_to_file(FILE* file, ChessGame* game) {
    char* color = game->currentPlayerWhite ? WHITE_COLOR_STR : BLACK_COLOR_STR;
    fprintf(file, "%s\n", color);
    print_settings_str(file, game->settings);
    print_board_to_file(game->board, file);
    game->saved = true;
    return true;
}

/**
 Return the path to the saved game slot slot
 */
char* get_saved_game_path(int slot) {
    char* path = (char*)malloc(strlen(LOAD_GAME_FILE_NAME_FORMAT)); // -1 because %d is a single char after format
    sprintf(path, LOAD_GAME_FILE_NAME_FORMAT, slot);
    return path;
}
/**
 Loads a pre-saved game from the given slot. If the game does not exist, returns NULL
 */
ChessGame* load_game_from_slot_index(int slot, int guiMode) {
    char* path = get_saved_game_path(slot);
    ChessGame* game = load_from_file(path, guiMode);
    free(path);
    return game;
}
/**
 Saves the given game to the given slot index. True iff saved.
 */
bool save_game_to_slot_index(int slot, ChessGame* game) {
    char* path = get_saved_game_path(slot);
    FILE* f = fopen(path, "w");
    if (f==NULL) return false;
    bool r = save_game_to_file(f, game);
    fclose(f);
    free(path);
    return r;
}
