//
//  MinimaxAI.c
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 25/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "MinimaxAI.h"
#include <stdlib.h>
#include <limits.h>
enum ScoreForPiece{
    KingScore = 100,
    QueenScore = 9,
    RookScore = 5,
    BishopAndKnightScore = 3,
    PawnScore = 1
};
#define UNDEFINED_SCORE_FOR_PIECE 0
#define TIE_SCORE_CONST 0
#define LOSE_SCORE_CONST -1000
#define SCORE_COLOR_CONST(isWhite) (isWhite? 1:-1)
#define MAX(a,b) ((a>b) ? a:b)
#define MIN(a,b) ((a<b) ? a:b)
/**
 get score for a game piece
 
 @param gamePiece the game piece to score
 @return score for game piece(negative for black,positive for white)
 */
int _score_for_game_piece(GamePiece* gamePiece){
    int score = UNDEFINED_SCORE_FOR_PIECE;
    switch (gamePiece->typeOfGamePiece) {
        case King:
            score = KingScore;
            break;
        case Queen:
            score = QueenScore;
            break;
        case Rook:
            score = RookScore;
            break;
        case Bishop:
        case Knight:
            score = BishopAndKnightScore;
            break;
        case Pawn:
            score = PawnScore;
            break;
        default:
            break;
    }
    return score*SCORE_COLOR_CONST(gamePiece->isWhite);
}


/**
 score a board
 
 @param board board to score
 @warning doesn't check for tie or check!!!
 @return score of board acordding to scoring function, negative score means situtaion is better(as defined by scoring function) for black player and postive score means situation is better(in the same meaning) for white player
 */
int _score_board_helper(ChessBoard* board){
    int score = 0;
    for(int i = 0;i<PLAYERS_COUNT;i++){
        for(int j=0;j<NUMBER_OF_GAME_PIECE_TYPES;j++){
            List* typedAndColoredGamePiecesList = board->gamePieces[i][j];
            for(int gamePieceIndex=0;gamePieceIndex<get_items_count(typedAndColoredGamePiecesList);gamePieceIndex++){
                GamePiece* gamePieceToScore = get_element(typedAndColoredGamePiecesList, gamePieceIndex);
                score+= _score_for_game_piece(gamePieceToScore);
            }
        }
    }
    return score;
}

/**
 score a board
 
 @param board board to score
 @return score of board acordding to scoring function, negative score means situtaion is better(as defined by scoring function) for black player and postive score means situation is better(in the same meaning) for white player
 */
int _score_board(ChessBoard* board,bool isWhite){
    
    bool thereAreNoPossibleMoves = !there_are_possible_moves(board, isWhite);
    if(thereAreNoPossibleMoves){
        bool isCheck = is_check(board,isWhite);
        if(isCheck){
            return LOSE_SCORE_CONST;
        }
        else{
            return TIE_SCORE_CONST;
        }
    }
    else{
        return _score_board_helper(board);
    }
    
    
}
int minimax(ChessBoard* board,int depth,int alpha,int beta,bool isWhite){
    
    
    List* possibleMoves = get_all_possible_moves(board, isWhite);
    if(depth == 0||get_items_count(possibleMoves)==0){
        
        return _score_board(board,isWhite);
    }
    if(isWhite){
        int bestMove = INT_MIN;
        for(int moveIndex = 0;moveIndex<get_items_count(possibleMoves);moveIndex++){
            ChessBoard* copiedBoard = copy_board(board);
            DetailedMove* detailedMove = get_element(possibleMoves, moveIndex);
            make_move_on_board(copiedBoard, copiedBoard->boardData[detailedMove->fromCell.row][detailedMove->fromCell.column], &detailedMove->move.cell);
            bestMove = MAX(bestMove, minimax(copiedBoard, depth-1, alpha, beta, !isWhite));
            alpha = MAX(alpha, bestMove);
            free_chess_board(copiedBoard);
            if(beta<=alpha){
                break;
            }
        }
        free_list(possibleMoves);
        return bestMove;
        
    }else{
        int bestMove = INT_MAX;
        for(int moveIndex = 0;moveIndex<get_items_count(possibleMoves);moveIndex++){
            ChessBoard* copiedBoard = copy_board(board);
            DetailedMove* detailedMove = get_element(possibleMoves, moveIndex);
            make_move_on_board(copiedBoard, copiedBoard->boardData[detailedMove->fromCell.row][detailedMove->fromCell.column], &detailedMove->move.cell);
            bestMove = MIN(bestMove, minimax(copiedBoard, depth-1, alpha, beta, !isWhite));
            beta = MIN(beta,bestMove);
            free_chess_board(copiedBoard);
            if(beta<=alpha){
                break;
            }
        }
        free_list(possibleMoves);
        return bestMove;
    }
    
    
}
DetailedMove* get_best_move(ChessBoard* board,bool isWhite,int depth){
    depth = 4;
    DetailedMove* bestMoveTemp = NULL;
    int bestMoveValue = INT_MIN;
    List* possibleMoves = get_all_possible_moves(board, isWhite);
    for(int moveIndex = 0;moveIndex<get_items_count(possibleMoves);moveIndex++){
        ChessBoard* copiedBoard = copy_board(board);
        DetailedMove* detailedMove = get_element(possibleMoves, moveIndex);
        make_move_on_board(copiedBoard, copiedBoard->boardData[detailedMove->fromCell.row][detailedMove->fromCell.column], &detailedMove->move.cell);
        int score = minimax(copiedBoard, depth-1, INT_MIN, INT_MAX, !isWhite);
        free_chess_board(copiedBoard);
        if(!isWhite){
            score = -score;
        }
        if(score>bestMoveValue){
            bestMoveValue = score;
            bestMoveTemp = detailedMove;
        }
        
    }
    if(bestMoveTemp == NULL){
        free_list(possibleMoves);
        return NULL;
    }
    else{
        DetailedMove* realBestMove = malloc(sizeof(DetailedMove));
        memcpy(realBestMove, bestMoveTemp, sizeof(DetailedMove));
        free_list(possibleMoves);
        return realBestMove;
    }
}
