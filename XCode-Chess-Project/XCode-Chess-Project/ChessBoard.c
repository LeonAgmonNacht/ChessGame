//
//  ChessBoard.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessBoard.h"
#include "GamePieces.h"
#define WHITE_PAWNS_ROW_INDEX 1
#define BLACK_PAWNS_ROW_INDEX 6
#define WHITE_NON_PAWNS_ROW_INDEX 0
#define BLACK_NON_PAWNS_ROW_INDEX 7
#define NON_PAWN_ROW_INDEX(isWhite) isWhite? WHITE_NON_PAWNS_ROW_INDEX : BLACK_NON_PAWNS_ROW_INDEX
#define PAWN_ROW_INDEX(isWhite) isWhite ? WHITE_PAWNS_ROW_INDEX:BLACK_PAWNS_ROW_INDEX
#define PIECES_INDEX(isWhite) isWhite ? 1:0
/**
 THE ARRAY OF THE PIECES AS ORDERED IN CHESS GAME IN THE FIRST ROW FROM THE SIDE OF THE PLAYER
 */
#define FIRST_ROW_OF_PIECES {Rook,Knight,Bishop,King,Queen,Bishop,Knight,Rook}
/**
 fill the board empty spaces with null
 
 @param board the board to fill
 */
static void fill_board_data_with_null(ChessBoard *board) {
    for (int row = 0; row<BOARD_SIZE; row ++)
        for (int col = 0; col<BOARD_SIZE; col++)
            (board->boardData)[row][col] = NULL;
}

/**
 get a piece single instance
 
 @param board board of game
 @param type the type of the piece
 @param isWhite boolean of is white
 @return the single instance piece on the board
 */
GamePiece* get_piece_with_type_and_color(ChessBoard* board, PieceType type,bool isWhite){
    return board->allGamePieces[isWhite ? 1:0][type];
}


/**
 init pawns for specific color
 
 @param board board of game
 @param isWhite is white boolean
 */
static void init_pawns_for_color(ChessBoard* board, bool isWhite){
    for (int columnIndex = 0; columnIndex<BOARD_SIZE; columnIndex++)
    {
        List* pawnsList = board->gamePieces[PIECES_INDEX(isWhite)][Pawn];
        GamePiece* pawn = init_game_piece(Pawn,isWhite,columnIndex,PAWN_ROW_INDEX(isWhite));
        insert_item(pawnsList, pawn);
        board->boardData[pawn->gamePieceCell.row][pawn->gamePieceCell.column] = get_last_element(pawnsList);
        free(pawn);
    }
}
/**
 init pawns when board is created
 
 @param board the game board
 */
static void init_pawns(ChessBoard *board) {
    init_pawns_for_color(board, true);
    init_pawns_for_color(board, false);
}


/**
 init non pawn pieces with given color
 
 @param board board
 @param isWhite bool that says if pieces are white
 */
static void _init_non_pawn_pieces_with_color(ChessBoard* board,bool isWhite){
    static const PieceType piecesArray[] = FIRST_ROW_OF_PIECES;
    
    for(int i = 0;i<BOARD_SIZE;i++){
        List* list = board->gamePieces[PIECES_INDEX(isWhite)][piecesArray[i]];
        GamePiece* gamePiece = init_game_piece(piecesArray[i], isWhite,i,NON_PAWN_ROW_INDEX(isWhite));
        insert_item(list, gamePiece);
        board->boardData[gamePiece->gamePieceCell.row][gamePiece->gamePieceCell.column] = get_last_element(list);
        free(gamePiece);
        //TODO:DECIDE IF I WANT TO ADD GAMEPIECE OR POINTER TO GAME PIECE, NOW IT'S NOT A POINTER
        
        
    }
    //init_game_piece(<#PieceType pieceType#>, <#bool isWhite#>)
}
/**
 init the not pawn pieces when board is created
 
 @param board the board of game
 
 */
static void _init_non_pawn_pieces(ChessBoard *board) {
    _init_non_pawn_pieces_with_color(board, true);
    _init_non_pawn_pieces_with_color(board, false);
}

static void _init_pieces_lists(ChessBoard* board){
    for(int i = 0;i<PLAYERS_COUNT;i++){
        for(int j =0;j<NUMBER_OF_GAME_PIECE_TYPES;j++){
            board->gamePieces[i][j] = init_list(2, sizeof(GamePiece));
        }
    }
}
// TODO: Implement
void _init_board_data(ChessBoard* board) {
    
    // init NULL:
    
    fill_board_data_with_null(board);
    
    _init_pieces_lists(board);
    
    
    // init pawns:
    init_pawns(board);
    // non pawns = a nick name for the row of pieces of white player(not the pawns one, the second one)
    _init_non_pawn_pieces(board);
    
}


/**
 initalizng board pieces single isntances,
 
 @param board the board of the game
 */
void _init_pieces(ChessBoard* board) {
    
    for(int i =0;i<PLAYERS_COUNT;i++){
        for(int j=King;j<=Pawn;j++){
            //board->allGamePieces[i][j]=init_game_piece(j, i == 0 ? false:true);
        }
    }
    
}


//TODO:LEON CHECK
// renderer will be NULL if game mode is console
ChessBoard* init_game_board(int mode, SDL_Renderer* renderer) {
    
    // MEM:
    
    ChessBoard* board = (ChessBoard *) malloc(sizeof(GamePiece*) * sizeof(ChessBoard));
    _init_pieces(board);
    _init_board_data(board);
    // INIT:
    
    return board;
}

char* _get_row_data_string(ChessBoard* board, int row) {
    char* data = (char*) malloc(BOARD_SIZE*2);
    for (int col = 0; col<BOARD_SIZE*2; col+=2) {
        data[col] = board->boardData[row][col/2] == NULL ? '_' : get_char_from_game_piece(board->boardData[row][col/2]);
        data[col+1] = ' ';
    }
    return data;
}

/**
 Prints the given board to f
 */
void print_board_to_file(ChessBoard* board, FILE* f) {
    for (int row = BOARD_SIZE-1; row>=0; row--) {
        char* rowData = _get_row_data_string(board, row);
        fprintf(f, "%d| %s|\n", (row), rowData);
        free(rowData);
        
    }
    fprintf(f, "  -----------------\n");
    fprintf(f, "   A B C D E F G H\n");
}


/**
 Preforms a move
 */
void preform_board_move(ChessBoard*board, Cell* startCell, Cell* destCell) {
    board->boardData[destCell->row][destCell->column] = board->boardData[startCell->row][startCell->column];
    board->boardData[startCell->row][startCell->column] = NULL;
}
/**
 Returns true iff the given board represents a game that has ended
 */
bool check_game_ended(ChessBoard* borad) {
    return false;
    // TODO: implement.
}

void free_chess_board(ChessBoard* board) {
    // TODO: meltzer implement i dont know what u did with all there textures.
    free(board);
}
