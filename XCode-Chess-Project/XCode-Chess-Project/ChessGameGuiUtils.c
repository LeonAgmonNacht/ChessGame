//
//  ChessGameGuiUtils.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ChessGameGuiUtils.h"
#include "LoadGameScreen.h"
#include <SDL.h>
#include <SDL_video.h>
#include "ChessGameUtils.h"

/**
 Initiate a GUI proccess to load a game from a saved slot
 */
void _handle_gui_load(ChessGame* game) {
    
    SDL_HideWindow(game->boardWindow->window);
    LoadGameScreen* loadScreen = init_load_game_screen(true); // true because we are loading from a slot, and not saving to one.
    int slotIndex = wait_for_slot_choice(loadScreen, true); // true because we are loading from a slot, and not saving to one.
    free_load_game_screen(loadScreen);
    if (slotIndex == -1) { // Back
        SDL_ShowWindow(game->boardWindow->window);
    }
    else {
        ChessGame* newGame = load_game_from_slot_index(slotIndex, GAME_MODE_WITH_GUI);
        if (newGame != NULL) {
            free_game(game);
            game = newGame;
            draw_chess_board_according_to_state(game->board, game->boardWindow, NULL);
        }
    }
}

/**
 Initiate a GUI proccess to save the given game
 */
void _handle_gui_save(ChessGame* game) {
    
    SDL_HideWindow(game->boardWindow->window);
    LoadGameScreen* loadScreen = init_load_game_screen(false); // false because we are saving to a slot, and not loading from one.
    int slotIndex = wait_for_slot_choice(loadScreen, false); // false because we are saving to a slot, and not loading from one.
    free_load_game_screen(loadScreen);
    if (slotIndex == -1) { // Back
        SDL_ShowWindow(game->boardWindow->window);
    }
    else {
        save_game_to_slot_index(slotIndex, game);
    }
}

/**
 Returns a new CellColor from the move type and the given cell
 */
CellColor* _get_cell_color_from_type_and_cell(Cell* cell, MoveType type) {
    CellColor* cc = (CellColor*)malloc(sizeof(CellColor));
    if (type == ThreatendCaptureType) {cc->r = 241; cc->g = 196; cc->b = 15; cc-> a = 1.0;}
    else if (type == ThreatendType) {cc->r = 214; cc->g = 48; cc->b = 49; cc->a = 1.0;}
    else if (type == CaptureType) {cc->r = 46; cc->g = 204; cc->b = 113; cc->a = 1.0;}
    else if (type == RegularType) {cc->r = 99; cc->g = 110; cc->b = 114; cc->a = 1.0;}
    cc->col = cell->column; cc->row = cell->row;
    return cc;
}

/**
 Returns a list of CellColor that will be used to color the tiles in custom colors.
 The cells should be highlighted by four different colors: a standard square (should not be in the returned list), a threatened square (that is, a square that is threatened by an opponent piece), a capture square (occupied by an opponent piece), or a square that is both threatened and a capture square.
 */
List* _get_cell_colors_list_for_index(Cell* cell, ChessGame* game) {
    List* moves = get_posibble_moves(cell, game->board);
    List* rList = init_list_without_copy(get_items_count(moves), free);
    for (int i = 0; i<(int)get_items_count(moves); i++) {
        Move* move = (Move*) get_element(moves, i);
        CellColor* cc = _get_cell_color_from_type_and_cell(&(move->cell), move->moveType);
        insert_item(rList, cc);
        
    }
    free_list(moves);
    return rList;
}

/**
 Handle a click in the chess borad itself
 Returns the status of the game after the move.
 */
GameFinishedStatusEnum _handle_gui_board_move(ChessGame* game, Cell** cell, ChessWindowAction* action) {
    
    GameFinishedStatusEnum gameStatus = GameFinishedActionUndetermined;
    
    if (*cell == NULL) {
        if (!verify_valid_start_pos_move(game, action->cellClicked)) return false;
        *cell = action->cellClicked;
        
        if (action->cellClicked != NULL && action->isRightClick) {
            draw_chess_board_according_to_state(game->board, game->boardWindow,
                                                _get_cell_colors_list_for_index(action->cellClicked, game));
            
        }
        
        action->cellClicked = NULL; // So it won't be freed
    }
    else {
        if (!verify_valid_end_pos_move(game, *cell, action->cellClicked)) {
            free(*cell);
            *cell = NULL;
            return false;
        }
        preform_chess_game_move(game, *cell, action->cellClicked);
        gameStatus = get_game_status(game);
        free(*cell);
        *cell = NULL;
        
    }
    return gameStatus;
}

/**
 Play a game which has gui type gui game until it is finished. Return the reason.
 NOTE: a load/save/undo/move_piece commands are handled internally.
 */
GameFinishedStatusEnum play_gui_game(ChessGame* game) {
    
    Cell* cell = NULL; // Will be used to store the first-cell-clicked by the user, next cell-click will cause a move.
    GameFinishedStatusEnum gameStatus = GameFinishedActionUndetermined; // Current game status after the last move
    while (true) {
        
        if (game->settings->gameMode == GAME_MODE_AI && (game->settings->userColor == WHITECOLOR) != game->currentPlayerWhite) {
            preform_computer_move(game);
            gameStatus = get_game_status(game);
            if (gameStatus == GameFinishedActionCheck) present_check_dialog();
            if (gameStatus == GameFinishedActionMate) present_checkmate_dialog();
        }
        int buttonId = - 1; // Used if an alert message was presented.
        ChessWindowAction* action = wait_for_move_or_action(game->boardWindow);
        
        // Outer responsibillity:
        if (action->actionType==QuitClicked) {
            free_window_action(action);
            if (!game->saved) present_exit_game_dialog(&buttonId);
            if (buttonId == YES_BUTTON_ID) _handle_gui_save(game);
            else if (buttonId == CANCEL_BUTTON_ID) continue;
            return GameFinishedActionQuit;
        }
        else if (action->actionType == RestartClicked) {
            free_window_action(action);
            return GameFinishedActionReset;
        }
        else if (action->actionType == MainMenuClicked){
            free_window_action(action);
            if (!game->saved) present_exit_game_dialog(&buttonId);
            if (buttonId == YES_BUTTON_ID) _handle_gui_save(game);
            else if (buttonId == CANCEL_BUTTON_ID) continue;
            return GameFinishedActionMainMenu;
        }
        // Inner responsibillity:
        else if (action->actionType == LoadClicked) {
            free_window_action(action);
            _handle_gui_load(game);
        }
        else if (action->actionType == SaveClicked) {
            free_window_action(action);
            _handle_gui_save(game);
        }
        else if (action->actionType == UndoClicked) {
            free_window_action(action);
            undo_game_move(game);
            draw_chess_board_according_to_state(game->board, game->boardWindow, NULL);
            
        }
        // Move handling:
        else if (action->actionType == BoardMove && gameStatus != GameFinishedActionMate) {
            if (!(gameStatus == GameFinishedActionDraw || gameStatus == GameFinishedActionMate)) {
                gameStatus = _handle_gui_board_move(game, &cell, action);
                if (gameStatus == GameFinishedActionCheck) present_check_dialog();
                if (gameStatus == GameFinishedActionMate) present_checkmate_dialog();
                free_window_action(action);
            }
        }
    }
    return GameFinishedActionQuit;
}
