//
//  main.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include <stdio.h>
#include "ChessGame.h"

int main(int argc, const char * argv[]) {
    
    // Initilize Game:
    // TODO: Change to actual game mode.
    SDL_Init(SDL_INIT_VIDEO);
    
    chessGame * game = init_game(GAME_MODE_WITH_GUI);
    draw_chess_board_according_to_state(game->board, game->boardWindow);
    SDL_Delay(10000);
    SDL_Quit();
    
}
