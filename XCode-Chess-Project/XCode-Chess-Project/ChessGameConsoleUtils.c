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
#include "ChessGamesLogic.h"
#include "Move.h"
#define SHOULD_END_GAME(action) (action == GameFinishedActionQuit || action == GameFinishedActionDraw || action == GameFinishedActionMate || action == GameFinishedActionReset)

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
 Prints a message if someone has won, if there is a tie, or if there is a check. Returns the game state
 */
GameFinishedStatusEnum _print_console_game_status_message(ChessGame* game) {
    GameFinishedStatusEnum status = get_game_status(game);
    if (status == GameFinishedActionMate) {
        printf("Checkmate! %s player wins the game\n", (game->currentPlayerWhite ? WHITE_COLOR_STR : BLACK_COLOR_STR));
    }
    else if (status == GameFinishedActionCheck) {
        printf("Check: %s king is threatened\n", game->currentPlayerWhite ? WHITE_COLOR_STR : BLACK_COLOR_STR);
    }
    else if (status == GameFinishedActionDraw) {
        printf("The game ends in a draw\n");
    }
    return status;
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
    
    Cell* startC = (Cell*)malloc(sizeof(Cell));
    startC->row = startRowStr[0] - '0'; startC->column = startColStr[0] - 'A';
    Cell* endC = (Cell*)malloc(sizeof(Cell));
    endC->row = destRowStr[0] - '0'; endC->column = destColStr[0] - 'A';
    
    DetailedMove* move = (DetailedMove*)malloc(sizeof(DetailedMove));
    move->fromCell = *startC;
    move->move = (Move){*endC, RegularType};
    IsValidCases moveState = isValidMove(game->board, move);
    free(move);
    
    if (game->board->boardData[startRowIndex][startColIndex] == NULL) {
        printf("Invalid position on the board\n");
    }
    if (game->board->boardData[startRowIndex][startColIndex]->isWhite != game->currentPlayerWhite) {
        printf("The specified position does not contain your piece\n");
    }
    else if (moveState != ValidMove) {

        free(move);
        if (moveState == IlegalMove) printf("Illegal move\n");
        else if (moveState == CheckAndCheckAfterwards) printf("Illegal move: king is still threatened\n");
        else if (moveState == NewCheck) printf("Ilegal move: king will be threatened\n");
        
    }
    else {
        preform_chess_game_move(game, startC, endC);
        GameFinishedStatusEnum status = _print_console_game_status_message(game);
        free(startC); free(endC);
        return status;
    }
    free(startC); free(endC);
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
        printf("Enter your move (%s player):\n", (game->currentPlayerWhite ? WHITE_COLOR_STR : BLACK_COLOR_STR));
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
            return result;
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
    
    // Handle first move:
    if (game->currentPlayerWhite) {
        GameFinishedStatusEnum action = console_preform_user_move(game);
        if (SHOULD_END_GAME(action)) { return action; }
    }
    
    while (true) {
        // Play comp move if needed:
        if (game->settings->gameMode == GAME_MODE_AI) {
            preform_computer_move(game);
            GameFinishedStatusEnum action = _print_console_game_status_message(game);
            if (action == GameFinishedActionDraw || action == GameFinishedActionMate) {
                return action;
            }
        }
        else {
            GameFinishedStatusEnum action = console_preform_user_move(game);
            if (SHOULD_END_GAME(action)) { return action; }
        }
        // Play user move:
        GameFinishedStatusEnum action = console_preform_user_move(game);
        if (SHOULD_END_GAME(action)) { return action; }
    }
}
