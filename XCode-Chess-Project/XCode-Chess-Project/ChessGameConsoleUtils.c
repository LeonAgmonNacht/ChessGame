//
//  ChessGameConsoleUtils.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ChessGameConsoleUtils.h"
#include "ChessGamesLogic.h"
#include "ChessGameUtils.h"
#include "Move.h"
#define SHOULD_END_GAME(action) if (action == GameFinishedActionQuit || action == GameFinishedActionDrawOrMate || action == GameFinishedActionReset) { return action; }

/**
 Check that the given strs are given indexes in the chess board.
 */
bool _check_string_valid_indexes(char* rowStr, char* colStr) {
    if (strlen(rowStr) != 1 || strlen(colStr) != 1) return false;
    if ((rowStr[0] - '0') < 0 || (rowStr[0] - '0') > BOARD_SIZE) return false;
    if ((colStr[0] - 'A') < 0 || (colStr[0] - 'A') > BOARD_SIZE) return false;
    return true;
}
/**
 Handles the case of a get moves command.
 */
void _handle_get_moves_command(ChessGame* game, char* rowStr, char* colStr) {
    
    if (!_check_string_valid_indexes(rowStr, colStr)) {
        printf("Invalid position on the board\n");
        return;
    }
    
    int rowIndex = rowStr[0] - '0';
    int colIndex = colStr[0] - 'A';
    
    if (game->board->boardData[rowIndex][colIndex] == NULL) {
        printf("The specified position does not contain a player piece\n");
        return;
    }
    else {
        Cell* cell = (Cell*)malloc(sizeof(Cell));
        cell->row = rowIndex; cell->column = colIndex;
        List* list = get_posibble_moves(cell, game->board);
        for (int i = 0; i<get_items_count(list); i++) {
            Move* move = (Move*)get_element(list, i);
            printf("<%d,%d>", rowIndex, colIndex);
            printf((move->moveType == ThreatendType) ? "*" : "");
            printf((move->moveType == CaptureType) ? "^" : "");
            printf("\n");
        }
        free_list(list);
        free(cell);
    }
    
}
/**
 Handle the case of a move command.
 */
GameFinishedStatusEnum _handle_move_command(ChessGame* game,
                                            char* startRowStr, char* startColStr,
                                            char* destRowStr, char* destColStr) {
    
    if (!_check_string_valid_indexes(startRowStr, startColStr) ||
        !_check_string_valid_indexes(destRowStr, destColStr)) {
        printf("Invalid position on the board\n");
        return GameFinishedActionUndetermined;
    }
    int startRowIndex = startRowStr[0] - '0';
    int startColIndex = startColStr[0] - 'A';
    if (game->board->boardData[startRowIndex][startColIndex] == NULL) {
        printf("Invalid position on the board\n");
        return GameFinishedActionUndetermined;
    }
    if (game->board->boardData[startRowIndex][startColIndex]->isWhite != game->currentPlayerWhite) {
        printf("The specified position does not contain your piece\n");
    }
    else if (false) {
        // TODO: meltzer you need to check if this is a valid move, if not print :
        // "Illegal move\n" and return.
        // If the king is in "Check" and after the move it will still be in "Check" print:
        // "Illegal move: king is still threatened\n". and return.
        // If the move causes the king to be threatened (Check) print "Ilegal move: king will be threatened\n" and return.
        // If more then one of the aboce occurres print only the first one (in that order!!)
        // Please read this part of the doc...
        
    }
    else {
        Cell* startC = (Cell*)malloc(sizeof(Cell));
        startC->row = startRowStr[0] - '0'; startC->column = startColStr[0] - 'A';
        Cell* endC = (Cell*)malloc(sizeof(Cell));
        endC->row = destRowStr[0] - '0'; endC->column = destColStr[0] - 'A';
        preform_board_move(game->board, startC, endC);
        // TODO: make sure this is the only place this is ran...
        game->currentPlayerWhite = !game->currentPlayerWhite;
        free(startC); free(endC);
        
        // TODO: Meltzer print messages as per doc, i cant continue without your methods.
        // NOTE: if a mate or draw occured dont forget to return it...
    }
    return GameFinishedActionUndetermined;
}

/**
 Preforms a console user move
 */
GameFinishedStatusEnum console_preform_user_move(ChessGame* game) {
    print_board_to_file(game->board, stdout);
    char* currentLine = (char*)malloc(MAX_LINE_LENGTH+1);
    while (true) {
        
        // Get Line:
        printf("Enter your move (%s player):\n", (game->currentPlayerWhite ? "white" : "black"));
        if (fgets(currentLine, MAX_LINE_LENGTH, stdin)== NULL) { free(currentLine); break; }
        currentLine[strcspn(currentLine, "\n")] = '\0';
        LineData* data = parse_line(currentLine);
        
        if (data == NULL) {
            printf(INVALID_COMMAND_STRING);
            free(data);
            continue;
        }
        
        if (data->commandType == QUIT) {
            free(currentLine); free(data);
            return GameFinishedActionQuit;
        }
        else if (data->commandType == RESET_COMMAND) {
            free(currentLine); free(data);
            return GameFinishedActionReset;
        }
        else if (data->commandType == SAVE_COMMAND) {
            FILE* file = fopen(data->firstArg, "w");
            if (file == NULL) {
                printf("File cannot be created or modified\n");
                continue;
            } else {
                if (save_game_to_file(file, game)) {
                    printf("Game saved to: %s\n", data->firstArg);
                }
                else {
                    printf("File cannot be created or modified\n");
                }
                free(currentLine); free(data); fclose(file);
                return GameFinishedActionUndetermined;
            }
        }
        else if (data->commandType == UNDO_COMMAND) {
            free(data);
            UndoMoveCallReturnType undoResult = undo_game_move(game);
            if (undoResult == UndoNoHistory) printf("Empty history, no move to undo\n");
            if (undoResult == UndoSuccess) {
                free(currentLine);
                return GameFinishedActionUndetermined;
            }
        }
        else if (data->commandType == GET_MOVES_COMMAND) {
            _handle_get_moves_command(game, data->firstArg, data->secondArg);
            free(data); free(currentLine);
            return GameFinishedActionUndetermined;
        }
        else if (data->commandType == MOVE_COMMAND) {
            GameFinishedStatusEnum result = _handle_move_command(game,
                                                                 data->firstArg,
                                                                 data->secondArg,
                                                                 data->thirdArg,
                                                                 data->fourthArg);
            free(data); free(currentLine);
            if (result == GameFinishedActionDrawOrMate) {
                return GameFinishedActionDrawOrMate;
            }
            return GameFinishedActionUndetermined;
        }
        else {
            printf(INVALID_COMMAND_STRING);
            free(data);
        }
        
    }
    return GameFinishedActionUndetermined;
}

/**
 Play a console game until it is finished. Returns the reason for ending game.
 NOTE: a load/save/undo/move_piece commands are handled internally.
 */
GameFinishedStatusEnum play_console_game(ChessGame* game) {
    
    // Will be used to store the first-cell-clicked by the user, next cell-click will cause a move:
    Cell* cell = NULL;
    // true if the game has ended -> disables moving the pieces but allowing the user to choose his next action:
    bool gameHasEnded = false;
    
    // Handle first move:
    if (game->currentPlayerWhite) {
        GameFinishedStatusEnum action = console_preform_user_move(game);
        SHOULD_END_GAME(action)
    }
    
    while (true) {
        if (game->settings->gameMode == GAME_MODE_AI) {
            GameFinishedStatusEnum action = preform_computer_move(game);
            if (action == GameFinishedActionDrawOrMate) {
                return action;
            }
        }
        else {
            GameFinishedStatusEnum action = console_preform_user_move(game);
            SHOULD_END_GAME(action);
        }
        GameFinishedStatusEnum action = console_preform_user_move(game);
        SHOULD_END_GAME(action);
    }
}
