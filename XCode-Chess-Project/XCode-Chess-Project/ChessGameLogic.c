//
//  ChessGameMovesValidator.c
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 28/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessGamesLogic.h"
#include <stdbool.h>


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
#define FEASABLE_MOVES_ROOK_INITIAL_LIST_SIZE_CONST 16
#define FEASABLE_MOVES_BISHOP_INITIAL_LIST_SIZE_CONST 16
#define FEASABLE_MOVES_PAWN_INITIAL_LIST_SIZE_CONST 2
#define FEASABLE_MOVES_KING_INITIAL_LIST_SIZE_CONST 4
#define FEASABLE_MOVES_KNIGHT_INITIAL_LIST_SIZE_CONST 4
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



/**
 add simple move(capture/regular)
 
 @param movesList moves list to add to
 @param board board we play on
 @param cellToMoveTo the cell we move the gamepiece to
 @param gamePiece the game piece we move
 @return true if move is feasable, false if it's not(not in board or same color piece has pre-occupied the cell)
 */
static bool _add_simple_move( List *movesList,ChessBoard *board, const Cell *cellToMoveTo, GamePiece *gamePiece) {
    if(!_check_if_cell_in_board(cellToMoveTo->row, cellToMoveTo->column)){
        return false;
    }
    else if (board->boardData[cellToMoveTo->row][cellToMoveTo->column] == NULL){
        Move* regularMove = malloc(sizeof(Move));
        init_move(regularMove, cellToMoveTo->row, cellToMoveTo->column, RegularType);
        insert_item(movesList, regularMove);
    }
    else if((board->boardData[cellToMoveTo->row][cellToMoveTo->column]->isWhite)^(gamePiece->isWhite)){
        Move* captureMove = malloc(sizeof(Move));
        init_move(captureMove, cellToMoveTo->row, cellToMoveTo->column, CaptureType);
        insert_item(movesList, captureMove);
        return false;
    }
    else{
        return false;
    }
    return true;
}

/**
 add feasable knight moves
 
 @param movesList the list to add to
 @param pieceOnBoardCell piece on board
 @param board board to add to
 */
void _add_knight_feasable_moves(List* movesList, Cell* pieceOnBoardCell,ChessBoard* board){
    GamePiece* gamePiece = board->boardData[pieceOnBoardCell->row][pieceOnBoardCell->column];
    for(int i = 0;i<=Up;i++){
        Cell cellToMoveTo;
        cellToMoveTo.row = pieceOnBoardCell->row + REGULAR_VERTICAL_MOVE_FACTOR(i)*FIRST_MOVE_KNIGHT_TILES_NUMBER_CONST;
        for(int j = Left;j<=Right;j++){
            cellToMoveTo.column = pieceOnBoardCell->column +REGULAR_HORIZONTAL_MOVE_FACTOR(j);
            _add_simple_move(movesList, board, &cellToMoveTo, gamePiece);
        }
    }
    for(int i = Left;i<=Right;i++){
        Cell cellToMoveTo;
        cellToMoveTo.column = pieceOnBoardCell->column + REGULAR_HORIZONTAL_MOVE_FACTOR(i)*FIRST_MOVE_KNIGHT_TILES_NUMBER_CONST;
        for(int j = 0;j<=Up;j++){
            cellToMoveTo.row = pieceOnBoardCell->row + REGULAR_VERTICAL_MOVE_FACTOR(j);
            _add_simple_move(movesList, board, &cellToMoveTo, gamePiece);
            
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
    for(int i = 1;i<= bound; i++){
        Cell cellToMoveTo;
        cellToMoveTo.row  = pieceOnBoardCell->row + (REGULAR_VERTICAL_MOVE_FACTOR(direction)*i);
        cellToMoveTo.column = pieceOnBoardCell->column + (REGULAR_HORIZONTAL_MOVE_FACTOR(direction)*i);
        if(!_add_simple_move(movesList, board, &cellToMoveTo, gamePiece)){
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
        Cell cellToMoveTo;
        cellToMoveTo.row =pieceOnBoardCell->row+(DIAGONAL_VERTICAL_MOVE_FACTOR(direction))*i;
        cellToMoveTo.column=pieceOnBoardCell->column+(DIAGONAL_HORIZONTAL_MOVE_FACTOR(direction))*i;
        if(!_add_simple_move(movesList, board, &cellToMoveTo, gamePiece)){
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
    if(_check_if_cell_in_board(pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column)){
        if(board->boardData[pawnOnBoardToMove->row+moveConst][pawnOnBoardToMove->column]==NULL){
            Move* move = malloc(sizeof(Move));
            init_move(move, pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column, RegularType);
            insert_item(movesForPawn, move);
        }
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
    const int moveConst = PAWN_SPECIAL_MOVE_CONST( board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column]->isWhite);
    const int regularPawnMoveConst = PAWN_MOVE_CONST(board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column]->isWhite);
    // location const
    const int locationConst = PAWN_SPECIAL_MOVE_LOACTION_CONST(board->boardData[pawnOnBoardToMove->row][pawnOnBoardToMove->column]->isWhite);
    if((pawnOnBoardToMove->row ==locationConst) && (board->boardData[pawnOnBoardToMove->row+moveConst][pawnOnBoardToMove->column]==NULL)){
        if(board->boardData[pawnOnBoardToMove->row+regularPawnMoveConst][pawnOnBoardToMove->column]==NULL){
            Move* move = malloc(sizeof(Move));
            init_move(move, pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column, RegularType);
            insert_item(movesForPawn, move);
        }
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
    if(_check_if_cell_in_board(pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column+diagonalConst)){
        
        GamePiece* diagonalRightPiece = board->boardData[pawnOnBoardToMove->row+moveConst][pawnOnBoardToMove->column+diagonalConst];
        //check if there is a piece
        if(diagonalRightPiece != NULL){
            //check if the diagonal piece is otherwise colored
            if(diagonalRightPiece->isWhite ^ pawn->isWhite){
                Move* move = malloc(sizeof(Move));
                init_move(move,  pawnOnBoardToMove->row+moveConst, pawnOnBoardToMove->column+diagonalConst, CaptureType);
                insert_item(movesForPawn, move);
                
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
static List* _get_feasable_pawn_moves(ChessBoard *board, Cell *pawnOnBoardToMove) {
    List* movesForPawn = init_list(FEASABLE_MOVES_PAWN_INITIAL_LIST_SIZE_CONST, free,copy_move);
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
 state, just gets the moves that a piece can do, doesn't check if the move is threatend or so either
 */
List* _get_feasable_moves(Cell* pieceOnBoardToMove,ChessBoard* board){
    List* moves = NULL;
    GamePiece* piece = board->boardData[pieceOnBoardToMove->row][pieceOnBoardToMove->column];
    switch (piece->typeOfGamePiece) {
        case Pawn:
            moves = _get_feasable_pawn_moves(board, pieceOnBoardToMove);
            break;
        case Bishop:
            moves = init_list(FEASABLE_MOVES_BISHOP_INITIAL_LIST_SIZE_CONST, free,copy_move);
            _add_diagonal_feasable_moves(moves, pieceOnBoardToMove, board, BOARD_SIZE-1);
            break;
        case Rook:
            moves = init_list(FEASABLE_MOVES_ROOK_INITIAL_LIST_SIZE_CONST, free,copy_move);
            _add_regular_feasable_moves(moves, pieceOnBoardToMove, board, BOARD_SIZE-1);
            break;
        case Queen:
            moves = init_list(FEASABLE_MOVES_ROOK_INITIAL_LIST_SIZE_CONST+FEASABLE_MOVES_KNIGHT_INITIAL_LIST_SIZE_CONST, free,copy_move);
            _add_regular_feasable_moves(moves, pieceOnBoardToMove, board, BOARD_SIZE-1);
            _add_diagonal_feasable_moves(moves, pieceOnBoardToMove, board, BOARD_SIZE-1);
            break;
        case King:
            moves = init_list(FEASABLE_MOVES_KING_INITIAL_LIST_SIZE_CONST, free,copy_move);
            _add_regular_feasable_moves(moves, pieceOnBoardToMove, board, 1);
            _add_diagonal_feasable_moves(moves, pieceOnBoardToMove, board, 1);
            break;
        case Knight:
            moves = init_list(FEASABLE_MOVES_KNIGHT_INITIAL_LIST_SIZE_CONST, free,copy_move);
            _add_knight_feasable_moves(moves, pieceOnBoardToMove, board);
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
 check if check accourd against player
 
 @param board the current board
 @param isWhite the player to check for: true means check for white player
 @return check if in the current board the player requested is under check
 */
bool is_check(ChessBoard* board , bool isWhite){
    
    const int ourPlayerindex = PIECES_INDEX(isWhite);
    const int otherPlayerIndex = PIECES_INDEX(!isWhite);
    GamePiece* ourKing = get_last_element(board->gamePieces[ourPlayerindex][King]);
    for(int typeIndex = 0;typeIndex<NUMBER_OF_GAME_PIECE_TYPES;typeIndex++){
        for(int pieceIndex = 0;pieceIndex< (int)get_items_count(board->gamePieces[otherPlayerIndex][typeIndex]);pieceIndex++){
            GamePiece* gamePiece = get_element(board->gamePieces[otherPlayerIndex][typeIndex],
                                               (size_t)pieceIndex);
            List* feasableMoves = _get_feasable_moves(&(gamePiece->gamePieceCell), board);
            for(int moveIndex = 0 ;moveIndex<(int)get_items_count(feasableMoves);moveIndex++){
                Move* move = get_element(feasableMoves,
                                         (size_t)moveIndex);
                if((move->cell.column == ourKing->gamePieceCell.column)&&(move->cell.row==ourKing->gamePieceCell.row) ){
                    free_list(feasableMoves);
                    return true;
                }
            }
            free_list(feasableMoves);
        }
    }
    
    return false;
}


/**
 get posibble *legal* moves for player,doesn't check if they are threathend
 @param pieceOnBoardToMoveCell the cell where we want to check the possible moves for
 @param board the current board of the game
 @return legal moves in a list,please notice that a move would be a Move struct
 */
static List* _get_posibble_moves(Cell* pieceOnBoardToMoveCell,ChessBoard* board){
    List* moves = _get_feasable_moves(pieceOnBoardToMoveCell, board);
    List* possibleMoves = init_list(DEFAULT_LIST_SIZE,free,copy_move);
    
    for(int moveIndex = 0;moveIndex<(int)get_items_count(moves);moveIndex++){
        ChessBoard* copiedBoard = copy_board(board);
        Move* move = get_element(moves, (size_t)moveIndex);
        GamePiece* gamePieceToMove = copiedBoard->boardData[pieceOnBoardToMoveCell->row][pieceOnBoardToMoveCell->column];
        make_move_on_board(copiedBoard, gamePieceToMove, &(move->cell));
        if(!is_check(copiedBoard, gamePieceToMove->isWhite)){
            Move* copiedMove = copy_move(move);
            insert_item(possibleMoves, copiedMove);
        }
        
        free_chess_board(copiedBoard);
    }
    
    free_list(moves);
    return possibleMoves;
}

/**
 check if piece is thretend
 @warning because king is a special piece, this won't work for king as for piece, it is not considered threatend if the threatning piece
 is protecting it's king from check, which is not correct for king(check)
 
 @param board chess board
 @param pieceCell cell of piece to check if is threatend
 @return true if piece is threatend or false if it is not
 */
//bool _is_piece_threathend(ChessBoard* board, Cell* pieceCell){
//
//
//    for(int i = 0 ; i<=INDEX_OF_LAST_ROW_IN_BOARD;i++){
//        for(int j  = 0;j<=INDEX_OF_LAST_COLUMNS_IN_BOARD;j++){
//            // check if there is a piece
//            if(board->boardData[i][j] !=NULL){
//                //check if the piece is oppenet
//                if(board->boardData[i][j]->isWhite ^ board->boardData[pieceCell->row][pieceCell->column]->isWhite){
//                    Cell checkedCell;
//                    checkedCell.row = i;
//                    checkedCell.column = j;
//                    List* listOfPossibleMoves = _get_posibble_moves(&checkedCell, board);
//                    for(int i = 0;i<get_items_count(listOfPossibleMoves);i++){
//                        Move* move = (Move*)get_element(listOfPossibleMoves, i);
//                        if(are_cells_equal(&(move->cell), pieceCell)){
//                            free_list(listOfPossibleMoves);
//                            listOfPossibleMoves = NULL;
//                            return true;
//                        }
//                    }
//                    free_list(listOfPossibleMoves);
//                }
//            }
//        }
//    }
//    return false;
//}


/**
 check if suspectedThreatningPieceCell threatens suspectedThreatendPieceCell
 
 @param board board of game
 @param suspectedThreatningPieceCell cell we suspect is threatning
 @param suspectedThreatendPieceCell cell suspected as threathend
 @return true if and only if  the suspected threatning cell threatns the suspectedThreatendPieceCell
 */
bool _does_piece_threaten_other(ChessBoard*board, Cell* suspectedThreatningPieceCell,Cell* suspectedThreatendPieceCell){
    List* possibleMovesOfSuspectedThreatningPiece = _get_posibble_moves(suspectedThreatningPieceCell, board);
    for(int moveIndex = 0;moveIndex<(int)get_items_count(possibleMovesOfSuspectedThreatningPiece);moveIndex++){
        Move* possibleMoveOfsuspectedThreatningPiece = get_element(possibleMovesOfSuspectedThreatningPiece,
                                                                   (size_t)moveIndex);
        Cell* cellSuspectedThreatningPieceCanMoveTo = &(possibleMoveOfsuspectedThreatningPiece->cell);
        if(are_cells_equal(cellSuspectedThreatningPieceCanMoveTo, suspectedThreatendPieceCell)){
            free_list(possibleMovesOfSuspectedThreatningPiece);
            return true;
        }
    }
    free_list(possibleMovesOfSuspectedThreatningPiece);
    return false;
}


/**
 check if piece is threatend
 
 @param board board we play on
 @param suspectedThreatendPieceCell suspected threatend piece cell
 @return true if the piece is threatend by one of the second palyers pieces
 */
bool _new_is_piece_threathed(ChessBoard* board, Cell* suspectedThreatendPieceCell){
    GamePiece* pieceToCheck = board->boardData[suspectedThreatendPieceCell->row][suspectedThreatendPieceCell->column];
    if(pieceToCheck == NULL){
        printf("problem");
        return false;
    }else{
        bool isThePieceWhite  = pieceToCheck->isWhite;
        bool isOtherPlayerColor = !isThePieceWhite;
        int const otherPlayerPiecesIndex  = PIECES_INDEX(isOtherPlayerColor);
        for(int i = 0;i<NUMBER_OF_GAME_PIECE_TYPES;i++){
            List* otherPlayerPiecesWithType = board->gamePieces[otherPlayerPiecesIndex][i];
            for(int pieceIndex = 0;pieceIndex<(int)get_items_count(otherPlayerPiecesWithType);pieceIndex++){
                GamePiece* suspectedThreatningPiece = get_element(otherPlayerPiecesWithType,
                                                                  (size_t)pieceIndex);
                Cell* suspectedThreatningPieceCell =  &(suspectedThreatningPiece->gamePieceCell);
                if(_does_piece_threaten_other(board,suspectedThreatningPieceCell, suspectedThreatendPieceCell)){
                    return true;
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
    List* possibleMoves = _get_posibble_moves(pieceOnBoardToMove, board);
    
    for(int moveIndex =0;moveIndex<(int)get_items_count(possibleMoves);moveIndex++){
        Move* move = get_element(possibleMoves,
                                 (size_t)moveIndex);
        ChessBoard* copiedBoard = copy_board(board);
        GamePiece* gamePieceToMove = copiedBoard->boardData[pieceOnBoardToMove->row][pieceOnBoardToMove->column];
        make_move_on_board(copiedBoard, gamePieceToMove, &(move->cell));
        if(_new_is_piece_threathed(copiedBoard, &(gamePieceToMove->gamePieceCell)))
        {
            if(move->moveType == RegularType){
                move->moveType = ThreatendType;
            }
            else if(move->moveType == CaptureType){
                move->moveType = ThreatendCaptureType;
            }
        }
        free_chess_board(copiedBoard);
    }
    
    return possibleMoves;
}


/**
 check if there are possible moves
 
 @param board board of game
 @param isWhite is player we are checking for white
 @return true iff there are possible moves
 */
bool there_are_possible_moves(ChessBoard* board,bool isWhite){
    const int myPiecesIndex = PIECES_INDEX(isWhite);
    for(int i =0;i<NUMBER_OF_GAME_PIECE_TYPES;i++){
        List* typedAndColoredPiecesList = board->gamePieces[myPiecesIndex][i];
        for(int pieceIndex = 0;pieceIndex<(int)get_items_count(typedAndColoredPiecesList);pieceIndex++){
            GamePiece* piece = get_element(typedAndColoredPiecesList, (size_t)pieceIndex);
            List* possibleMoves = _get_posibble_moves(&(piece->gamePieceCell), board);
            size_t possibleMovesCount = get_items_count(possibleMoves);
            free_list(possibleMoves);
            if(possibleMovesCount>0)
            {
                return true;
            }
            
        }
    }
    return false;
}


/**
 get all possible moves (as detailed moves)
 @warning not typed correctly!!
 @param board board of game
 @param isWhite color of player we want to move
 @return list of detailed moves
 */
List* get_all_possible_moves(ChessBoard* board,bool isWhite){
    List* allPossibleMoves = init_list(DEFAULT_LIST_SIZE, free,copy_detailed_move);
    const int myPiecesIndex = PIECES_INDEX(isWhite);
    for(int i =0;i<NUMBER_OF_GAME_PIECE_TYPES;i++){
        List* typedAndColoredPiecesList = board->gamePieces[myPiecesIndex][i];
        for(int pieceIndex = 0;pieceIndex<(int)get_items_count(typedAndColoredPiecesList);pieceIndex++){
            GamePiece* piece = get_element(typedAndColoredPiecesList, (size_t)pieceIndex);
            List* possibleMoves = _get_posibble_moves(&(piece->gamePieceCell), board);
            size_t possibleMovesCount = get_items_count(possibleMoves);
            if(possibleMovesCount>0)
            {
                for(int i = 0;i<(int)possibleMovesCount;i++){
                    DetailedMove* detailedMove = malloc(sizeof(DetailedMove));
                    Cell from = piece->gamePieceCell;
                    Move* theMove = get_element(possibleMoves, (size_t)i);
                    detailedMove->move = *theMove;
                    detailedMove->fromCell = from;
                    insert_item(allPossibleMoves, detailedMove);
                }
            }
            free_list(possibleMoves);
            
        }
    }
    return allPossibleMoves;
    
}
/**
 check if there is tie when next player to move is the white one
 
 @param board board to check the tie in
 @param isWhite the player that should move
 @return true if the player we check for is tied, false otherwise
 */
bool is_tie(ChessBoard* board,bool isWhite){
    if(!is_check(board, isWhite)&&(!there_are_possible_moves(board, isWhite))){
        return true;
    }
    return false;
}
/**
 check if the game is in match state
 
 @param board board to check the match in
 @param isWhite player indicator to check if the piece matched is white
 @return true if there is a match against the player false otherwise
 */
bool is_match(ChessBoard* board, bool isWhite){
    if(is_check(board, isWhite)&&(!there_are_possible_moves(board, isWhite))){
        return true;
    }
    return false;
}
/**
 check if move is valid
 
 @param board board to move on
 @param move the move to make
 @return one of the IsVlaidCases according to the move
 */

IsValidCases isValidMove(ChessBoard* board, DetailedMove* move) {
    GamePiece* piece = board->boardData[move->fromCell.row][move->fromCell.column];
    if(piece == NULL){
        return IlegalMove;
    }
    else{
        
        List* feasableMoves = _get_feasable_moves(&piece->gamePieceCell, board);
        bool theMoveIsFeasable = false;
        for(int i = 0;i<(int)get_items_count(feasableMoves);i++){
            Move* pMove = (Move*)get_element(feasableMoves, (size_t)i);
            if(are_cells_equal(&pMove->cell, &move->move.cell) ){
                free_list(feasableMoves);
                theMoveIsFeasable = true;
                break;
            }
        }
        
        if(!theMoveIsFeasable){
            free_list(feasableMoves);
            return IlegalMove;
        }
        bool isWhite = piece->isWhite;
        if(is_check(board, isWhite)){
            ChessBoard* newBoard = copy_board(board);
            GamePiece* pieceToMoveOnBoard = newBoard->boardData[piece->gamePieceCell.row][piece->gamePieceCell.column];
            make_move_on_board(newBoard, pieceToMoveOnBoard, &move->move.cell);
            if(is_check(newBoard, piece->isWhite)){
                return CheckAndCheckAfterwards;
            }
            free_chess_board(newBoard);
        }
        else{
            ChessBoard* newBoard = copy_board(board);
            GamePiece* pieceToMoveOnBoard = newBoard->boardData[piece->gamePieceCell.row][piece->gamePieceCell.column];
            make_move_on_board(newBoard, pieceToMoveOnBoard, &move->move.cell);
            if(is_check(newBoard, true)){
                return NewCheck;
            }
            free_chess_board(newBoard);
        }
        List* possibleMoves =_get_posibble_moves(&move->fromCell, board);
        for(int i = 0;i<(int)get_items_count(possibleMoves);i++){
            Move* pMove = get_element(possibleMoves, (size_t)i);
            if(are_cells_equal(&pMove->cell, &move->move.cell) ){
                free_list(possibleMoves);
                return ValidMove;
            }
        }
        free_list(possibleMoves);
        return IlegalMove;
    }
    return ValidMove;
}
