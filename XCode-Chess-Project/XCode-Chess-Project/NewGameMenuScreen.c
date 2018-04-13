//
//  NewGameMenuScreen.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 04/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "NewGameMenuScreen.h"
#include "SDLUtils.h"
#include "ChessGame.h"
#include <stdbool.h>

// MARK: Window Related Consts:

#define STARTING_DEFFICULTY 1
#define STARTING_COLOR false
#define STARTING_GAME_MODE GAME_MODE_2_PLAYERS
#define NEW_GAME_WIN_TITLE "New Game"
#define NEW_GAME_WIN_W 400
#define NEW_GAME_WIN_H 450
#define BUTTONS_WIDTH 100
#define BUTTONS_HEIGHT 50
#define BUTTONS_PADDING 25
#define INITIAL_HEIGHT 50
#define DIFFS_BUTTONS_H 60
#define DIFFS_BUTTONS_W 300
#define NUM_DIFFS_BUTTONS 5

// MARK: Textures Rects:

#define PLAYER1_RECT &(SDL_Rect){(NEW_GAME_WIN_W/2)-BUTTONS_WIDTH-(BUTTONS_PADDING/2),INITIAL_HEIGHT,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define PLAYER2_RECT &(SDL_Rect){(NEW_GAME_WIN_W/2)+(BUTTONS_PADDING/2),INITIAL_HEIGHT,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define DIFF_LABEL_RECT &(SDL_Rect){(NEW_GAME_WIN_W/2)-(BUTTONS_WIDTH/2),INITIAL_HEIGHT+BUTTONS_HEIGHT+BUTTONS_PADDING,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define DIFFS_BUTTON_RECT &(SDL_Rect){(NEW_GAME_WIN_W/2)-(DIFFS_BUTTONS_W/2),INITIAL_HEIGHT+BUTTONS_HEIGHT*2+BUTTONS_PADDING*2,DIFFS_BUTTONS_W,DIFFS_BUTTONS_H}
#define COLOR_BUTTON_RECT &(SDL_Rect){(NEW_GAME_WIN_W/2)-(BUTTONS_WIDTH/2),INITIAL_HEIGHT+BUTTONS_HEIGHT*3+BUTTONS_PADDING*3,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define BACK_BUTTON_RECT &(SDL_Rect){(NEW_GAME_WIN_W/2)-(BUTTONS_WIDTH)-(BUTTONS_PADDING/2),INITIAL_HEIGHT+BUTTONS_HEIGHT*4+BUTTONS_PADDING*4,BUTTONS_WIDTH,BUTTONS_HEIGHT}
#define START_BUTTON_RECT &(SDL_Rect){(NEW_GAME_WIN_W/2)+(BUTTONS_PADDING/2),INITIAL_HEIGHT+BUTTONS_HEIGHT*4+BUTTONS_PADDING*4,BUTTONS_WIDTH,BUTTONS_HEIGHT}


/**
 Creates the texture of the difficulty label and adds it to the window.
 */
void _draw_difficulty_label(SDL_Renderer* renderer) {
    SDL_Texture* diffLabel = load_texture("./GUI-Resources/diff_label.bmp", renderer);
    SDL_RenderCopy(renderer, diffLabel, NULL, DIFF_LABEL_RECT);
    SDL_DestroyTexture(diffLabel);
}
/**
 Draws the 1-player button as clicked or unclicked according to the given bool
 */
void _draw_1_player(SDL_Renderer* renderer, bool clicked) {
    SDL_Texture* onePlayer = load_texture(clicked ? "./GUI-Resources/player_1_mode_clicked.bmp":
                                           "./GUI-Resources/player_1_mode.bmp", renderer);
    SDL_RenderCopy(renderer, onePlayer, NULL, PLAYER1_RECT);
    SDL_DestroyTexture(onePlayer);
}
/**
 Draws the 2-players button as clicked or unclicked according to the given bool
 */
void _draw_2_players(SDL_Renderer* renderer, bool clicked) {
    SDL_Texture* twoPlayers = load_texture(clicked ? "./GUI-Resources/2_players_mode_clicked.bmp":
                                           "./GUI-Resources/2_players_mode.bmp", renderer);
    SDL_RenderCopy(renderer, twoPlayers, NULL, PLAYER2_RECT);
    SDL_DestroyTexture(twoPlayers);
}

/**
 Draws the difficulty buttons with the given one as clicked
 */
void _draw_diffs_buttons(SDL_Renderer* renderer, int diff) {
    char *path = (char*)malloc(strlen("./GUI-Resources/diffs_buttons_i_clicked.bmp")+1);
    sprintf(path, "./GUI-Resources/diffs_buttons_%d_clicked.bmp", diff);
    SDL_Texture* diffs_buttons = load_texture(path, renderer);
    SDL_RenderCopy(renderer, diffs_buttons, NULL, DIFFS_BUTTON_RECT);
    SDL_DestroyTexture(diffs_buttons);
    free(path);
}

/**
 Draws the black/white player buttons
 */
void _draw_player_color(SDL_Renderer* renderer, bool black) {
    SDL_Texture* playerColor = load_texture(black ? "./GUI-Resources/white_player.bmp":
                                            "./GUI-Resources/black_player.bmp", renderer);
    SDL_RenderCopy(renderer, playerColor, NULL, COLOR_BUTTON_RECT);
    SDL_DestroyTexture(playerColor);
}

/**
 Draws the start game button
 */
void _draw_start_game_button(SDL_Renderer* renderer) {
    SDL_Texture* playerColor = load_texture("./GUI-Resources/start_button.bmp", renderer);
    SDL_RenderCopy(renderer, playerColor, NULL, START_BUTTON_RECT);
    SDL_DestroyTexture(playerColor);
}
                                            
/**
 Draws the back game button
 */
void _draw_back_game_button(SDL_Renderer* renderer) {
    SDL_Texture* playerColor = load_texture("./GUI-Resources/back_button.bmp", renderer);
                                            SDL_RenderCopy(renderer, playerColor, NULL, BACK_BUTTON_RECT);
                                            SDL_DestroyTexture(playerColor);
}

/**
 Refresh the ui according to the given settings.
 */
void _refresh_screen(SettingsScreen* screen, int difficulty, bool userColor, int gameMode) {
    SDL_SetRenderDrawColor(screen->windowRenderer, 255, 255, 255, 0); // White
    SDL_RenderClear(screen->windowRenderer);
    if (gameMode == GAME_MODE_2_PLAYERS) {
        _draw_1_player(screen->windowRenderer, false);
        _draw_2_players(screen->windowRenderer, true);
    }
    else {
        _draw_1_player(screen->windowRenderer, true);
        _draw_2_players(screen->windowRenderer, false);
    }
    _draw_difficulty_label(screen->windowRenderer);
    _draw_diffs_buttons(screen->windowRenderer, difficulty);
    _draw_player_color(screen->windowRenderer, userColor);
    _draw_start_game_button(screen->windowRenderer);
    _draw_back_game_button(screen->windowRenderer);
}

/**
 Init all data and textures. NOTE that the data will be presented only when calling wait_for_start
 */
SettingsScreen* init_settings_screen() {
    SettingsScreen* menu = (SettingsScreen *) malloc(sizeof(SettingsScreen));
    menu->window = SDL_CreateWindow(
                                    NEW_GAME_WIN_TITLE,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    NEW_GAME_WIN_W,
                                    NEW_GAME_WIN_H,
                                    SDL_WINDOW_OPENGL);
    
    menu->windowRenderer = SDL_CreateRenderer(menu->window, -1, SDL_RENDERER_ACCELERATED);
    _refresh_screen(menu, STARTING_DEFFICULTY, STARTING_COLOR, STARTING_GAME_MODE);
    
    return menu;

}

/**
 Waits for events until the user click the start button, when he does returns the specified settings.
 If the back button was clicked NULL is returned.
 */
GameSettings* wait_for_start(SettingsScreen* screen) {

    int difficulty = STARTING_DEFFICULTY;
    bool userColorBlack = STARTING_COLOR;
    int gameMode = STARTING_GAME_MODE;
    SDL_RenderPresent(screen->windowRenderer);
    SDL_Event e;
    while (true) {
        
        SDL_WaitEvent(&e);
        if (e.type == SDL_MOUSEBUTTONUP) {
            int y = e.button.y;
            int x = e.button.x;
            
            // NOTE: Go through all clickable-ui-elements and check if they were pressed, act accordingly:
            
            if (is_in_rect(x, y, BACK_BUTTON_RECT)) {
                return NULL;
            }
            else if (is_in_rect(x, y, DIFFS_BUTTON_RECT)) {
                // Calculate the diff using the "section" the user clicked on:
                difficulty = 1 + (x-*DIFFS_BUTTON_RECT.x)/(*DIFFS_BUTTON_RECT.w/NUM_DIFFS_BUTTONS);
            }
            else if (is_in_rect(x, y, COLOR_BUTTON_RECT) && gameMode == GAME_MODE_2_PLAYERS) {
                userColorBlack = !userColorBlack;
            }
            else if (is_in_rect(x, y, PLAYER1_RECT)) {
                gameMode = GAME_MODE_AI;
            }
            else if (is_in_rect(x, y, PLAYER2_RECT)) {
                gameMode = GAME_MODE_2_PLAYERS;
            }
            else if (is_in_rect(x, y, START_BUTTON_RECT)) {
                GameSettings* settings = init_game_settings(difficulty, gameMode, userColorBlack ? BLACKCOLOR : WHITECOLOR, GAME_MODE_WITH_GUI);
                return settings;
            }
            _refresh_screen(screen, difficulty, userColorBlack, gameMode);
            SDL_RenderPresent(screen->windowRenderer);
        }
    }
}
/**
 Frees all resources.
 */
void free_settings_screen(SettingsScreen* screen){
    SDL_DestroyRenderer(screen->windowRenderer);
    SDL_DestroyWindow(screen->window);
    free(screen);
}

