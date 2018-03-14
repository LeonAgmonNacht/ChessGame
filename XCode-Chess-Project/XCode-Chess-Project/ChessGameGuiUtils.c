//
//  ChessGameGuiUtils.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ChessGameGuiUtils.h"
#include "LoadGameScreen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
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
            draw_chess_board_according_to_state(game->board, game->boardWindow);
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
 Handle a click in the chess borad itself
 Returns true iff the game has ended as a result of a move
 */
bool _handle_gui_board_move(ChessGame* game, Cell** cell, ChessWindowAction* action) {
    
    bool gameHasEnded = false;
    
    if (*cell == NULL) {
        if (!verify_valid_start_pos_move(game, action->cellClicked)) return false;
        *cell = action->cellClicked;
        action->cellClicked = NULL; // So it won't be freed
    }
    else {
        if (!verify_valid_end_pos_move(game, *cell, action->cellClicked)) return false;
        preform_chess_game_move(game, *cell, action->cellClicked);
        gameHasEnded = check_game_ended(game->board);
        *cell = NULL;
        free(*cell);
    }
    return gameHasEnded;
}

/**
 Play a game which has gui type gui game until it is finished. Return the reason.
 NOTE: a load/save/undo/move_piece commands are handled internally.
 */
GameFinishedStatusEnum play_gui_game(ChessGame* game) {
    
    Cell* cell = NULL; // Will be used to store the first-cell-clicked by the user, next cell-click will cause a move.
    bool gameHasEnded = false; // true if the game has ended -> disables moving the pieces but allowing the user to choose his next action.
    while (true) {
        ChessWindowAction* action = wait_for_move_or_action(game->boardWindow);
        
        // Outer responsibillity:
        if (action->actionType==QuitClicked) return GameFinishedActionQuit;
        else if (action->actionType == RestartClicked) return GameFinishedActionReset;
        else if (action->actionType == MainMenuClicked) return GameFinishedActionMainMenu;
        
        // Inner responsibillity:
        else if (action->actionType == LoadClicked) {
            _handle_gui_load(game);
        }
        else if (action->actionType == SaveClicked) {
            _handle_gui_save(game);
        }
        else if (action->actionType == UndoClicked) {
            undo_game_move(game);
            draw_chess_board_according_to_state(game->board, game->boardWindow);
            
        }
        // Move handling:
        else if (action->actionType == BoardMove && !gameHasEnded) {
            gameHasEnded = _handle_gui_board_move(game, &cell, action);
        }
        free_window_action(action);
    }
    return GameFinishedActionQuit;
}
