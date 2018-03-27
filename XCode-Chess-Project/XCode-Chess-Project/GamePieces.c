//
//  GamePieces.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "GamePieces.h"
#include <stdlib.h>
#include <unistd.h>
//the chars array is organized in the following way: <blacks array>,<whites array> in each array the chars are organized by the order of pieces types in PieceType enum
#define CHARS_FOR_PIECES_ARRAY {{'K','Q','R','B','N','M'},{'k','q','r','b','n','m'}}
#define PIECES_COUNT 6
#define PLAYERS_COUNT 2
#define WHITE_PIECES_CHAR_INDEX 1
#define BLACK_PIECES_CHAR_INDEX 0

char get_char_from_game_piece(GamePiece* gamePiece)
{
    //array of the pieces chars, first for black,second for white
    static const char charsForPieces[PLAYERS_COUNT][PIECES_COUNT] = CHARS_FOR_PIECES_ARRAY;
    // calculate the indexes of the matching char of the piece(if item is black we should go to the first array, else(white) go to the second array)
    return charsForPieces[gamePiece->isWhite ? WHITE_PIECES_CHAR_INDEX:BLACK_PIECES_CHAR_INDEX][gamePiece->typeOfGamePiece];
    
}
GamePiece* init_game_piece(PieceType pieceType, bool isWhite,int column, int row){
    GamePiece* piece = ((GamePiece*) malloc(sizeof(GamePiece)));
    piece->isWhite = isWhite;
    piece->typeOfGamePiece = pieceType;
    piece->gamePieceCell.row=row;
    piece->gamePieceCell.column = column;
    return piece;
}



