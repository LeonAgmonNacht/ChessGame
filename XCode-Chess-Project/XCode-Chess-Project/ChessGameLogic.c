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
#define INITIAL_DIAGONAL_LIST_SIZE 1
#define DIAGONAL_DIRECTION_COUNT 4
#define DIAGONAL_VERTICAL_MOVE_FACTOR(diagonalDirection) (diagonalDirection <= DownRight) ? -1:1
#define DIAGONAL_HORIZONTAL_MOVE_FACTOR(diagonalDirection) (diagonalDirection == DownLeft || diagonalDirection == UpLeft) ? -1:1
#define REGULAR_VERTICAL_MOVE_FACTOR(direction) ((direction < Left) ? ((direction == Down) ? -1 : 1 ):0)
#define REGULAR_HORIZONTAL_MOVE_FACTOR(direction) ((direction >= Left) ? ((direction == Left) ? -1 : 1):0)
#define FIRST_MOVE_KNIGHT_TILES_NUMBER_CONST 2
typedef enum DiagonalDirection{
    DownLeft,
    DownRight,
    UpRight,
    UpLeft
    
} DiagonalDirection;

typedef enum RegularDirection{
    Down,
    Up,
    Left,
    Right 
}RegularDirection;


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
/**
 check if cell in board

 @param row row
 @param column column
 @return true if cell is in board false otherwise
 */
static bool _check_if_cell_in_board(int row,int column){
    if((row < BOARD_SIZE) && (row>=0)){
        if((column<BOARD_SIZE) && (column>=0)){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    
    
}


void _add_knight_feasable_moves(List* movesList, Cell* pieceOnBoardCell,ChessBoard* board){
    
    for(int i = 0;i<=Up;i++){
        Cell cellToMoveTo;
        cellToMoveTo.row = pieceOnBoardCell->row + REGULAR_VERTICAL_MOVE_FACTOR(i)*FIRST_MOVE_KNIGHT_TILES_NUMBER_CONST;
        for(int j = Left;j<=Right;j++){
            cellToMoveTo.column = pieceOnBoardCell->column +REGULAR_HORIZONTAL_MOVE_FACTOR(i);
            
        }
    }
    for(int i = Left;i<=Right;i++){
        Cell cellToMoveTo;
        cellToMoveTo.column = pieceOnBoardCell->column + REGULAR_HORIZONTAL_MOVE_FACTOR(i)*FIRST_MOVE_KNIGHT_TILES_NUMBER_CONST;
        for(int j = 0;j<=Up;j++){
            cellToMoveTo.row = pieceOnBoardCell->row + REGULAR_VERTICAL_MOVE_FACTOR(i);
            
        }
    }
    
}

/**
 add forward feasable moves with a direction(same moves that a rook makes)

 @param movesList moves list to add feasable moves to
 @param pieceOnBoardCell piece on board to move regularly (like a rook)
 @param board board to move on
 @param bound the bound on the regular moves
 @param direction the direction of which to move the piece on
 */
void _add_regular_feasable_moves_with_direction(List* movesList, Cell* pieceOnBoardCell,ChessBoard* board,int bound, RegularDirection direction){
    GamePiece* gamePiece = board->boardData[pieceOnBoardCell->row][pieceOnBoardCell->column];
    for(int i = 0;i<= bound; i++){
        Cell cellToMove;
        cellToMove.row  = pieceOnBoardCell->row + (REGULAR_VERTICAL_MOVE_FACTOR(direction)*i);
        cellToMove.column = pieceOnBoardCell->column + (REGULAR_HORIZONTAL_MOVE_FACTOR(direction)*i);
        if(!_check_if_cell_in_board(cellToMove.row, cellToMove.column)){
            break;
        }
        else if (board->boardData[cellToMove.row][cellToMove.column] == NULL){
            Move regularMove;
            init_move(&regularMove, cellToMove.row, cellToMove.column, RegularType);
            insert_item(movesList, &regularMove);
        }
        else if((board->boardData[cellToMove.row][cellToMove.column]->isWhite)^(gamePiece->isWhite)){
            Move captureMove;
            init_move(&captureMove, cellToMove.row, cellToMove.column, CaptureType);
            insert_item(movesList, &captureMove);
        }
        else{
            break;
        }
        
    }
}
void _add_regular_feasable_moves(List* movesList,Cell* pieceOnBoardCell,ChessBoard* board,int bound){
    for(int i = 0;i<=Right;i++){
        _add_regular_feasable_moves_with_direction(movesList, pieceOnBoardCell, board, bound, (RegularDirection)i);
    }
}
/**
 add feasable daigonal moves with direction,dosen't detect capturing

 @param movesList movelist to add to
 @param pieceOnBoardCell the piece we want to diagonaly move
 @param board board to move in
 @param bound the bound of number of diagonal steps the piece can make(1 for king, 8 for bishop and queen)
 @param direction the direction of the diagonal
 */
void _add_diagonal_feasable_moves_with_direction(List* movesList,Cell* pieceOnBoardCell,ChessBoard* board,int bound,DiagonalDirection direction){
    GamePiece* gamePiece = board->boardData[pieceOnBoardCell->row][pieceOnBoardCell->column];
    for(int i = 1;i<=bound;i++){
        Cell cellToMove;
        cellToMove.row =pieceOnBoardCell->row+(DIAGONAL_VERTICAL_MOVE_FACTOR(direction))*i;
        cellToMove.column=pieceOnBoardCell->column+(DIAGONAL_HORIZONTAL_MOVE_FACTOR(direction))*i;
        if(!_check_if_cell_in_board(cellToMove.row, cellToMove.column)){
            break;
        }
        else if(board->boardData[cellToMove.row][cellToMove.column] == NULL){
            Move regularMove;
            init_move(&regularMove, cellToMove.row, cellToMove.column, RegularType);
            insert_item(movesList, &regularMove);
        }
        else if((board->boardData[cellToMove.row][cellToMove.column]->isWhite)^(gamePiece->isWhite)){
            Move captureMove;
            init_move(&captureMove, cellToMove.row, cellToMove.column, CaptureType);
            insert_item(movesList, &captureMove);
        }
        else{
            break;
        }
    }
}


/**
  get feasable daigonal moves
 @param moves the list of moves
 @param pieceOnBoardToMove the piece we want to diagonaly move
 @param board board to move in
 @param bound the bound of number of diagonal steps the piece can make(1 for king, 8 for bishop and queen)
 @warning no return beacuse queen has both diagonal and regular moves so better not create 2 lists
 */
void _add_diagonal_feasable_moves(List* moves,Cell* pieceOnBoardToMove,ChessBoard* board,int bound){
  
    for(int i = 0;i<=UpLeft;i++){
        _add_diagonal_feasable_moves_with_direction(moves, pieceOnBoardToMove, board, bound, (DiagonalDirection)i);
    }
    
}




/**
 adding regular feasable move
 
 @param board board
 @param movesForPawn list to add moves to
 @param pawnOnBoardToMove the pawn to move cell
 */
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
 get feasable moves for player
 
 @param pieceOnBoardToMove piece to move
 @param board board
 @return feasable moves for piece in cell,doesn't cehck if check can accour because of the move or if the game was in winning
 state, just gets the moves that a piece can do 
 */
List* _get_feasable_moves(Cell* pieceOnBoardToMove,ChessBoard* board){
    List* moves = NULL;
    GamePiece* piece = board->boardData[pieceOnBoardToMove->row][pieceOnBoardToMove->column];
    switch (piece->typeOfGamePiece) {
        case Pawn:
            moves = _get_feasable_pawn_moves(board, pieceOnBoardToMove);
            break;
        case Bishop:
            moves = init_list(16, sizeof(Move));
            _add_diagonal_feasable_moves(moves, pieceOnBoardToMove, board, BOARD_SIZE);
            break;
        case Rook:
            moves = init_list(16, sizeof(Move));
            _add_regular_feasable_moves(moves, pieceOnBoardToMove, board, BOARD_SIZE);
            break;
        case Queen:
            moves = init_list(32, sizeof(Move));
            break;
        case King:
            moves = init_list(2, sizeof(Move));
            break;
        case Knight:
            
        default:
            break;
    }
    
    return moves;
}
/**
 check if piece is thretend, warning because king is a special piece, this won't work for king as for piece is not considered threatend if the threatning piece
 is protecting it's king from check, which is not correct for king(check)
 
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
 get posibble *legal* moves for player
 @param pieceOnBoardToMove the piece on board we want to check the possible moves for
 @param board the current board of the game
 @return legal moves in a list,please notice that a move would be a Move struct
 */
List* get_posibble_moves(Cell* pieceOnBoardToMove,ChessBoard* board){
    List* moves = _get_feasable_moves(pieceOnBoardToMove, board);
    
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
    
    const int ourPlayerindex = PIECES_INDEX(isWhite);
    const int otherPlayerIndex = PIECES_INDEX(!isWhite);
    GamePiece* ourKing = get_last_element(board->gamePieces[ourPlayerindex][King]);
    for(int typeIndex = 0;typeIndex<NUMBER_OF_GAME_PIECE_TYPES;typeIndex++){
        for(int pieceIndex = 0;pieceIndex< get_items_count(board->gamePieces[otherPlayerIndex][typeIndex]);pieceIndex++){
            GamePiece* gamePiece = get_element(board->gamePieces[otherPlayerIndex][typeIndex],pieceIndex);
            List* feasableMoves = _get_feasable_moves(&(gamePiece->gamePieceCell), board);
            for(int moveIndex = 0 ;moveIndex<get_items_count(feasableMoves);moveIndex++){
                Move* move = get_element( feasableMoves,moveIndex);
                if((move->cell.column == ourKing->gamePieceCell.column)&&(move->cell.row==ourKing->gamePieceCell.row) ){
                    return true;
                }
            }
        }
    }
    
    return false;
}



