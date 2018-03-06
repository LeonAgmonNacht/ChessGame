//
//  NewGameMenuScreen.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 04/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef NewGameMenuScreen_h
#define NewGameMenuScreen_h
#include "ChessGame.h"
#include <stdio.h>

typedef struct _settings_screen {
    
} SettingsScreen;

SettingsScreen* init_settings_screen(void);
gameSettings* wait_for_start(SettingsScreen* screen);

#endif /* NewGameMenuScreen_h */
