//
//  MainMenuScreen.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 04/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef MainMenuScreen_h
#define MainMenuScreen_h

#include <stdio.h>

typedef struct _main_menu {
    
}
MainMenu;

MainMenu* init_main_menu(void);

typedef enum {
    MenuActionNewGame,
    MenuActionLoadGame,
    MenuActionQuit
} MainMenuAction;

MainMenuAction* wait_for_action(MainMenu* menu);
#endif /* MainMenuScreen_h */
