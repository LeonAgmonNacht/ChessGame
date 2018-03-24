//
//  ChessGameGuiUtils.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef ChessGameGuiUtils_h
#define ChessGameGuiUtils_h

#include <stdio.h>
#include "ChessGame.h"

/**
 Play a game which has gui type gui game until it is finished. Return the reason.
 NOTE: a load/save/undo/move_piece commands are handled internally.
 */
GameFinishedStatusEnum play_gui_game(ChessGame* game);

#endif /* ChessGameGuiUtils_h */
