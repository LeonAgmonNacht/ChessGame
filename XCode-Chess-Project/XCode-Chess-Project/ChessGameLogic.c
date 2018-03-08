//
//  ChessGameMovesValidator.c
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 28/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessGamesLogic.h"
#include <stdbool.h>
#define POSSIBLE_MOVES_LIST_INITIAL_SIZE_FOR_PAWN 3
#define INDEX_OF_LAST_ROW_IN_BOARD 7
#define INDEX_OF_LAST_COLUMNS_IN_BOARD 7
#define PAWN_MOVE_CONST(isWhite) isWhite ? 1:-1
#define PAWN_MOVE_CONST_BLACK 1
#define PAWN_SPECIAL_MOVE_LOACTION_CONST(isWhite) isWhite ? 1:6
#define PAWN_SPECIAL_MOVE_CONST(isWhite) isWhite ? 2:-2
#define PAWN_DIAGONAL_MOVING(toRight) toRight ? 1:-1


/**
 check if piece is thretend
 
 @param board chess board
 @param pieceCell cell of piece to check if is threatend
 @return true if piece is threatend or false if it is not
 */
bool _is_piece_threathend(ChessBoard* board, Cell* pieceCell){
    
    for(int i = 0 ; i<=INDEX_OF_LAST_ROW_IN_BOARD;i++){
        for(int j  = 0;j<=INDEX_OF_LAST_COLUMNS_IN_BOARD;j++){
            // check if there is a piece
            if(board->boardData[i][j] !=NULL){
                //check if the piece is oppenet
                if(board->boardData[i][j]->isWhite != board->boardData[pieceCell->row][pieceCell->column]->isWhite){
                    Cell checkedCell;
                    checkedCell.row = i;
                    checkedCell.column = j;
                    List* listOfPossibleMoves = get_posibble_moves(&checkedCell, board);
                    
                    for(int i = 0;i<get_items_count(listOfPossibleMoves);i++){
                        Move* m = (Move*)get_element(listOfPossibleMoves, i);
                        if(m->cell.column == pieceCell->column && m->cell.row == pieceCell->row){
                            free_list(listOfPossibleMoves);
                            listOfPossibleMoves = NULL;
                            return true;
                        }
                    }
                    free_list(listOfPossibleMoves);
                }
            }
        }
    }
    return false;
}


/**
 init a move

 @param move move to init
 @param row row
 @param column column
 @param moveType the move type
 */
static void init_move(Move* move, int row,int column,MoveType moveType){
    move->cell.row = row;
    move->cell.column = column;
    move->moveType = moveType;
}


static void _add_regular_feasable_pawn_move(ChessBoard *board, List *movesForPawn, Cell *pawnOnBoardToMove) {
    int moveConst = PAWN_MOVE_CONST(board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column]->isWhite);
    if(board->boardData[pawnOnBoardToMove->row+moveConst][pawnOnBoardToMove->column]==NULL){
        Move move;
        init_move(&move, pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column, RegularType);
        insert_item(movesForPawn, &move);
    }
}

/**
 add feasable starting move for pawn, checks if the pawn is in right position
 
 @param board board we play on
 @param movesForPawn list to add moves to
 @param pawnOnBoardToMove pawn to move on board
 */
static void _add_feasable_beggining_special_pawn_move(ChessBoard *board,List *movesForPawn,Cell *pawnOnBoardToMove){
    //move constant to add special moves
    int moveConst = PAWN_SPECIAL_MOVE_CONST( board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column]->isWhite);
    // location const
    int locationConst = PAWN_SPECIAL_MOVE_LOACTION_CONST(board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column]->isWhite);
    if((pawnOnBoardToMove->row ==locationConst) && (board->boardData[pawnOnBoardToMove->row+moveConst][pawnOnBoardToMove->column]==NULL)){
        Move move;
        init_move(&move, pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column, RegularType);
        insert_item(movesForPawn, &move);
    }
}

/**
 add diagonal capturing move for pawn if possible, it checks if possible
 
 @param board board we play on
 @param movesForPawn list to add moves to
 @param pawnOnBoardToMove cell pawn to move on board
 @param right is diagonal to right or to left(when looking from white size)
 */
static void _add_feasable_diagonal_pawn_move(ChessBoard *board, List *movesForPawn,  Cell *pawnOnBoardToMove,bool right) {
    int diagonalConst = PAWN_DIAGONAL_MOVING(right);
    GamePiece* pawn = board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column];
    int moveConst = PAWN_MOVE_CONST(board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column]->isWhite);
    //check if diagonal is in board borders
    if(((pawnOnBoardToMove->column + diagonalConst) <=INDEX_OF_LAST_COLUMNS_IN_BOARD) &&( pawnOnBoardToMove->column + diagonalConst >= 0)){
        GamePiece* diagonalRightPiece = board->boardData[pawnOnBoardToMove->row+moveConst][pawnOnBoardToMove->column+diagonalConst];
        //check if there is a piece
        if(diagonalRightPiece != NULL){
            //check if the diagonal piece is otherwise colored
            if(diagonalRightPiece->isWhite ^ pawn->isWhite){
                Move move;
                init_move(&move,  pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column+diagonalConst, CaptureType);
                insert_item(movesForPawn, &move);
            }
            
        }
    }
}
/**
 add diagonal capturing move for pawn if possible, it checks if possible(checks both diagonals)
 
 @param board board we play on
 @param movesForPawn list to add moves to
 @param pawnOnBoardToMove cell pawn to move on board
 */
static void _add_feasable_diagonal_pawn_moves(ChessBoard *board, List *movesForPawn,  Cell *pawnOnBoardToMove)
{
    _add_feasable_diagonal_pawn_move(board, movesForPawn, pawnOnBoardToMove, true);
     _add_feasable_diagonal_pawn_move(board, movesForPawn, pawnOnBoardToMove, false);
}
static void _add_feasable_diagonal_white_pawn_move(ChessBoard *board, List *movesForPawn, GamePiece *pawn, Cell *pawnOnBoardToMove,bool right) {
    int constant = right ? 1:-1;
    GamePiece* diagonalRightPiece = board->boardData[pawnOnBoardToMove->row+1][pawnOnBoardToMove->column+constant];
    if(diagonalRightPiece != NULL){
        //check if the diagonal piece is otherwise colored
        if(diagonalRightPiece->isWhite ^ pawn->isWhite){
            Move move;
            move.cell.row = pawnOnBoardToMove->row+1;
            move.cell.column = pawnOnBoardToMove->column+constant;
            move.moveType = CaptureType;
            insert_item(movesForPawn, &move);
        }
    }
}

/**
 add feasable daigonal right moves
 
 @param board board
 @param movesForPawn moves for pawns list to add items to
 @param pawn the pawn
 @param pawnOnBoardToMove  the pawn location on board
 */
static void _add_feasable_diagonal_right_white_pawn_move(ChessBoard *board, List *movesForPawn, GamePiece *pawn, Cell *pawnOnBoardToMove) {
    GamePiece* diagonalRightPiece = board->boardData[pawnOnBoardToMove->row+1][pawnOnBoardToMove->column+1];
    if(diagonalRightPiece != NULL){
        //check if the diagonal piece is otherwise colored
        if(diagonalRightPiece->isWhite ^ pawn->isWhite){
            Move move;
            move.cell.row = pawnOnBoardToMove->row+1;
            move.cell.column = pawnOnBoardToMove->column+1;
            move.moveType = CaptureType;
            insert_item(movesForPawn, &move);
        }
        
    }
}

/**
 add feasable daigonal left  moves
 
 @param board board
 @param movesForPawn moves for pawns list to add items to
 @param pawn  the pawn
 @param pawnOnBoardToMove the pawn location on board to move
 */
static void _add_feasable_diagonal_left_white_pawn_move(ChessBoard *board, List *movesForPawn, GamePiece *pawn, Cell *pawnOnBoardToMove) {
    GamePiece* diagonalLeftPiece = board->boardData[pawnOnBoardToMove->row+1][pawnOnBoardToMove->column-1];
    if(diagonalLeftPiece!=NULL){
        //check if the diagonal piece is otherwise colored
        if(diagonalLeftPiece->isWhite^pawn->isWhite){
            Move move;
            move.cell.row = pawnOnBoardToMove->row+1;
            move.cell.column = pawnOnBoardToMove->column-1;
            move.moveType = CaptureType;
            insert_item(movesForPawn, &move);
        }
    }
}


/**
 add all white pawn feasable
 
 @param board board to check on
 @param movesForPawn moves list to add to
 @param pawn the pawn to check
 @param pawnOnBoardToMove the pawn location
 */
static void _add_white_pawn_feasable_moves(ChessBoard *board, List *movesForPawn, GamePiece *pawn, Cell *pawnOnBoardToMove) {
    if(board->boardData[pawnOnBoardToMove->row+1][pawnOnBoardToMove->column]==NULL)
    {
        _add_regular_feasable_white_pawn_move(movesForPawn, pawnOnBoardToMove);
        
    }
    
    if(pawnOnBoardToMove->column + 1 < INDEX_OF_LAST_ROW_IN_BOARD){
        _add_feasable_diagonal_right_white_pawn_move(board, movesForPawn, pawn, pawnOnBoardToMove);
    }
    if(pawnOnBoardToMove->column > 0){
        _add_feasable_diagonal_left_white_pawn_move(board, movesForPawn, pawn, pawnOnBoardToMove);
    }
}

/**
 get feasable moves, doesn't check if check accours
 
 @param board the board of the game
 @param pawnOnBoardToMove the pawn to move
 @return the list of feasable moves
 */
static List * _get_feasable_pawn_moves(ChessBoard *board, Cell *pawnOnBoardToMove) {
    List* movesForPawn = init_list(POSSIBLE_MOVES_LIST_INITIAL_SIZE_FOR_PAWN, sizeof(Move));
    _add_feasable_diagonal_pawn_moves(board, movesForPawn, pawnOnBoardToMove);
    _add_feasable_beggining_special_pawn_move(board, movesForPawn, pawnOnBoardToMove);
    _add_regular_feasable_pawn_move(board, movesForPawn, pawnOnBoardToMove);
    return movesForPawn;
}

/**
 check possible moves for a pawn
 
 @param pawnOnBoardToMove pawn on board to move
 @param board the board of the game
 @return possible moves for the pawn, Move struct list
 @warning doesn't detect threatning
 */
List* _get_possible_moves_for_pawn(Cell* pawnOnBoardToMove,ChessBoard* board){
    
    return _get_feasable_pawn_moves(board, pawnOnBoardToMove);
}
/**
 get posibble *legal* moves for player
 @param pieceOnBoardToMove the piece on board we want to check the possible moves for
 @param board the current board of the game
 @return legal moves in a list,please notice that a move would be a Move struct
 */
List* get_posibble_moves(Cell* pieceOnBoardToMove,ChessBoard* board){
    List* moves = NULL;
    GamePiece* piece = board->boardData[pieceOnBoardToMove->row][pieceOnBoardToMove->column];
    switch (piece->typeOfGamePiece) {
        case Pawn:
            moves = _get_possible_moves_for_pawn(pieceOnBoardToMove, board);
            break;
            
        default:
            break;
    }
    
    return moves;
}


//List* _get_feasible_moves(Cell pieceOnBoardToMove,ChessBoard* board){
//
//
//}

/**
 check if check accourd agains player
 
 @param board the current board
 @param isWhite the player to check for: true means check for white player
 @return check if in the current board the player requested is under check
 */
bool is_check(ChessBoard* board , bool isWhite){
    
    return false;
}



