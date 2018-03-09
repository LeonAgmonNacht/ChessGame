//
//  GameSettings.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef GameSettings_h
#define GameSettings_h
#include "LineParser.h"
#include <stdio.h>

#define BLACKCOLOR 1
#define WHITECOLOR 2
#define GAME_MODE_WITH_GUI 0

// GAME MODES:
#define GAME_MODE_CONSOLE 2
#define GAME_MODE_AI 3
#define GAME_MODE_2_PLAYERS 4

#define MAX_LINE_LENGTH 3000

typedef struct _game_settings {
    int guiMode; // options: GAME_MODE_WITH_GUI, GAME_MODE_CONSOLE
    int gameMode; // options: GAME_MODE_AI, GAME_MODE_2_PLAYERS
    int difficulty; // options: 1-5
    int userColor; // options: BLACKCOLOR, WHITECOLOR;
} GameSettings;

GameSettings* get_game_settings();

#endif /* GameSettings_h */
