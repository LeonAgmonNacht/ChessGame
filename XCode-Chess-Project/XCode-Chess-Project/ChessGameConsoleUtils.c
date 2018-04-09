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

#define ROW_START_INDEX_CHAR '1'
#define COL_START_INDEX_CHAR 'A'

#define SHOULD_END_GAME(action) (action == GameFinishedActionQuit || action == GameFinishedActionDraw || action == GameFinishedActionMate || action == GameFinishedActionReset)

/**
 Check that the given strs are given indexes in the chess board.
 */
bool _check_string_valid_indexes(char* rowStr, char* colStr) {
    if (strlen(rowStr) != 1 || strlen(colStr) != 1)
    {
        return false;
    }
    //TODO:Problem here of leon of corse
    if ((rowStr[0] - ROW_START_INDEX_CHAR) < 0 || (rowStr[0] - ROW_START_INDEX_CHAR) > BOARD_SIZE)
    {
        return false;
    }
    if ((colStr[0] - COL_START_INDEX_CHAR) < 0 || (colStr[0] - COL_START_INDEX_CHAR) > BOARD_SIZE)
    {
        return false;
    }
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
    
    int rowIndex = rowStr[0] - ROW_START_INDEX_CHAR;
    int colIndex = colStr[0] - COL_START_INDEX_CHAR;
    
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
            printf("<%c,%c>", ROW_START_INDEX_CHAR + move->cell.row, COL_START_INDEX_CHAR + move->cell.column);
            printf((move->moveType == ThreatendType) ? "*" : "");
            printf((move->moveType == CaptureType) ? "^" : "");
            printf((move->moveType == ThreatendCaptureType) ? "*^" : "");
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
    int startRowIndex = startRowStr[0] - ROW_START_INDEX_CHAR;
    int startColIndex = startColStr[0] - COL_START_INDEX_CHAR;
    
    int destRowIndex = destRowStr[0] - ROW_START_INDEX_CHAR;
    int destColIndex = destColStr[0] - COL_START_INDEX_CHAR;
    
    Cell* startC = (Cell*)malloc(sizeof(Cell));
    startC->row = startRowIndex; startC->column = startColIndex;
    Cell* endC = (Cell*)malloc(sizeof(Cell));
    endC->row = destRowIndex; endC->column = destColIndex;
    
    DetailedMove* move = (DetailedMove*)malloc(sizeof(DetailedMove));
    move->fromCell = *startC;
    move->move = (Move){*endC, RegularType};
    IsValidCases moveState = isValidMove(game->board, move);
    free(move);
    
    if (game->board->boardData[startRowIndex][startColIndex] == NULL) {
        printf("Invalid position on the board\n");
    }
    else if (game->board->boardData[startRowIndex][startColIndex]->isWhite != game->currentPlayerWhite) {
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
            //free_line_data(data);
            continue;
        }
        
        if (data->commandType == QUIT) {
            free(currentLine); free_line_data(data);
            return GameFinishedActionQuit;
        }
        else if (data->commandType == RESET_COMMAND) {
            free(currentLine); free_line_data(data);
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
                free(currentLine); free_line_data(data); fclose(file);
                return GameFinishedActionUndetermined;
            }
        }
        else if (data->commandType == UNDO_COMMAND) {
            free_line_data(data);
            UndoMoveCallReturnType undoResult = undo_game_move(game);
            if (undoResult == UndoNoHistory) printf("Empty history, no move to undo\n");
            if (undoResult == UndoSuccess) {
                free(currentLine);
                return GameFinishedActionUndetermined;
            }
        }
        else if (data->commandType == GET_MOVES_COMMAND) {
            _handle_get_moves_command(game, data->firstArg, data->secondArg);
            free_line_data(data); free(currentLine);
            return GameFinishedActionUndetermined;
        }
        else if (data->commandType == MOVE_COMMAND) {
            GameFinishedStatusEnum result = _handle_move_command(game,
                                                                 data->firstArg,
                                                                 data->secondArg,
                                                                 data->thirdArg,
                                                                 data->fourthArg);
            free_line_data(data); free(currentLine);
            return result;
        }
        else {
            printf(INVALID_COMMAND_STRING);
            free_line_data(data);
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
    GameFinishedStatusEnum action = GameFinishedActionUndetermined;
    bool lastComputerMoveColor = game->currentPlayerWhite;
    
    while (action == GameFinishedActionUndetermined) {
        if (game->currentPlayerWhite == lastComputerMoveColor) {
            action = console_preform_user_move(game);
            if (SHOULD_END_GAME(action)) {
                return action;
            }
        }
        else break;
   }
    while (true) {
        // Play comp move if needed:
        if (game->settings->gameMode == GAME_MODE_AI && game->currentPlayerWhite != lastComputerMoveColor) {
            DetailedMove* move = preform_computer_move(game);
            lastComputerMoveColor = game->currentPlayerWhite;
            printf("Computer: move [%s] at <%c,%c> to <%c,%c>\n",
                   get_user_friendly_string_for_piece_in_cell(game->board, move->move.cell.row, move->move.cell.column),
                   ROW_START_INDEX_CHAR + move->fromCell.row, COL_START_INDEX_CHAR + move->fromCell.column,
                   ROW_START_INDEX_CHAR + move->move.cell.row, COL_START_INDEX_CHAR + move->move.cell.column);
            free(move);
            action = _print_console_game_status_message(game);
            if (action == GameFinishedActionDraw || action == GameFinishedActionMate) {
                return action;
            }
        }
        else {
            action = console_preform_user_move(game);
            if (SHOULD_END_GAME(action)) { return action; }
        }
        // Play user move:
        action = console_preform_user_move(game);
        if (SHOULD_END_GAME(action)) { return action; }
    }
}
