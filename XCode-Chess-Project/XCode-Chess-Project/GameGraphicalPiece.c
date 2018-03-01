//
//  GameGraphicalPiece.c
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 01/03/2018.
//  Copyright © 2018  daniel meltzer and leon agmon nacht. All rights reserved.
//

#include "GameGraphicalPiece.h"
//the paths array is organized in the following way: <blacks array>,<whites array> in each array the paths are organized by the order of pieces types in PieceType enum
#define IMGS_PATHS_FOR_PIECES_ARRAY {{"./GUI-Resources/Chess_kdt60.bmp","./GUI-Resources/Chess_qdt60.bmp","./GUI-Resources/Chess_rdt60.bmp","./GUI-Resources/Chess_bdt60.bmp","./GUI-Resources/Chess_ndt60.bmp","./GUI-Resources/Chess_pdt60.bmp"},{"./GUI-Resources/Chess_klt60.bmp","./GUI-Resources/Chess_qlt60.bmp","./GUI-Resources/Chess_rlt60.bmp","./GUI-Resources/Chess_blt60.bmp","./GUI-Resources/Chess_nlt60.bmp","./GUI-Resources/Chess_plt60.bmp"}}
#define PIECES_COUNT 6
#define PLAYERS_COUNT 2
#define WHITE_PIECES_PATH_INDEX 1
#define BLACK_PIECES_PATH_INDEX 0
GameGraphicalPiece* initalize_graphichal_game_piece(SDL_Renderer* renderer,GamePiece* gamePiece){
    
    GameGraphicalPiece* graphicalPiece = (GameGraphicalPiece*)malloc(sizeof(GameGraphicalPiece));
    graphicalPiece->gamePiece = gamePiece;
    
    return graphicalPiece;
}

//@TODO: CHECK if string is a valid terminology here
/**
 get the path for image when given a game piece struct using it's data

 @param gamePiece game piece that the data is needed for
 @return char array of paths(may be refferd as a string)
 
 */
const char* getPathForImgFromGamePiece(GamePiece* gamePiece){
    //array of the pieces chars, first for black,second for white
    static const char* pathsForGrpahicalPieces[PLAYERS_COUNT][PIECES_COUNT] = IMGS_PATHS_FOR_PIECES_ARRAY;
    const char* path = pathsForGrpahicalPieces[gamePiece->isWhite ? WHITE_PIECES_PATH_INDEX:BLACK_PIECES_PATH_INDEX][gamePiece->typeOfGamePiece];
    return path;
}
