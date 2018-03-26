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

#define BOARD_FILE_BOARD_ROW_LENGTH 20
/**
 THE ARRAY OF THE PIECES AS ORDERED IN CHESS GAME IN THE FIRST ROW FROM THE SIDE OF THE PLAYER
 */
#define FIRST_ROW_OF_PIECES {Rook,Knight,Bishop,King,Queen,Bishop,Knight,Rook}
/**
 fill the board empty spaces with null
 
 @param board the board to fill
 */
static void _fill_board_data_with_null(ChessBoard *board) {
    for (int row = 0; row<BOARD_SIZE; row ++)
        for (int col = 0; col<BOARD_SIZE; col++)
            (board->boardData)[row][col] = NULL;
}



/**
 init pawns for specific color
 
 @param board board of game
 @param isWhite is white boolean
 */
static void _init_pawns_for_color(ChessBoard* board, bool isWhite){
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
static void _init_pawns(ChessBoard *board) {
    _init_pawns_for_color(board, true);
    _init_pawns_for_color(board, false);
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
    
    _fill_board_data_with_null(board);
    
    _init_pieces_lists(board);
    
    
    // init pawns:
    _init_pawns(board);
    // non pawns = a nick name for the row of pieces of white player(not the pawns one, the second one)
    _init_non_pawn_pieces(board);
    
}



/**
 Inits a new game board.
 */
ChessBoard* init_game_board() {
    ChessBoard* board = (ChessBoard *) malloc(sizeof(GamePiece*) * sizeof(ChessBoard));
    _init_board_data(board);
    return board;
}

char* _get_row_data_string(ChessBoard* board, int row) {
    char* data = (char*) malloc(BOARD_SIZE*2+1);
    for (int col = 0; col<BOARD_SIZE*2; col+=2) {
        data[col] = board->boardData[row][col/2] == NULL ? EMPTY_SLOT_CHAR : get_char_from_game_piece(board->boardData[row][col/2]);
        data[col+1] = ' ';
    }
    data[BOARD_SIZE*2] = '\0';
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
 Gets this game board piece that is associated with the given symbol
 */
GamePiece* _get_game_piece_from_char( ChessBoard* board,char symbol) {
    return NULL;
    // TODO: meltzer implement
}

/**
 Loads a ChessBoard from the given (valid!) file.
 */
ChessBoard* load_board_from_file(FILE* file) {
    
    ChessBoard* board = init_game_board();
    
    char* currentRow = (char*)malloc(BOARD_FILE_BOARD_ROW_LENGTH+1);
    for (int row = BOARD_SIZE-1; row>=0; row--) {
        if (fgets(currentRow, MAX_LINE_LENGTH, file)== NULL) return NULL;
        char* currentCell = strtok(currentRow, " "); // Skip first
        for (int col = 0; col < BOARD_SIZE; col ++) {
            currentCell = strtok(NULL, " ");
            char pieceSymbol = currentCell[0];
            if (pieceSymbol == EMPTY_SLOT_CHAR) board->boardData[row][col] = NULL;
            else board->boardData[row][col] = _get_game_piece_from_char(board,pieceSymbol);
        }
    }
    
    free(currentRow);
    return board;
}
static void _copy_board_game_pieces(ChessBoard *board, int i, int j, ChessBoard *newBoard) {
    List* typedColoeedGamePiecesList = board->gamePieces[i][j];
    newBoard->gamePieces[i][j] =  copy_list(typedColoeedGamePiecesList);
    for(int gamePieceIndex = 0;gamePieceIndex<get_items_count(typedColoeedGamePiecesList);gamePieceIndex++){
        GamePiece* piece = get_element(typedColoeedGamePiecesList,gamePieceIndex);
        newBoard->boardData[piece->gamePieceCell.row][piece->gamePieceCell.column] = piece;
    }
}

/**
 copy board

 @param board original board
 @return new board
 */
ChessBoard* copy_board(ChessBoard* board){
    ChessBoard* newBoard = malloc(sizeof(ChessBoard));
    _fill_board_data_with_null(newBoard);
    for(int playerIndex = 0;playerIndex<PLAYERS_COUNT;playerIndex++){
        for(int pieceTypeIndex = 0;pieceTypeIndex<NUMBER_OF_GAME_PIECE_TYPES;pieceTypeIndex++){
            _copy_board_game_pieces(board, playerIndex, pieceTypeIndex, newBoard);
        }
    }
    return newBoard;
}
void free_chess_board(ChessBoard* board) {
    for(int playerIndex = 0;playerIndex<PLAYERS_COUNT;playerIndex++){
        for(int pieceTypeIndex = 0;pieceTypeIndex<NUMBER_OF_GAME_PIECE_TYPES;pieceTypeIndex++){
            free_list(board->gamePieces[playerIndex][pieceTypeIndex]);
        }
    }
    free(board);
}

/**
 make a move on board
 
 @param board board
 @param pieceToMove the piece to move
 @param cellToMoveTo the cell to move to the piece
 */
void make_move_on_board(ChessBoard* board, GamePiece* pieceToMove,Cell* cellToMoveTo){
    board->boardData[pieceToMove->gamePieceCell.row][pieceToMove->gamePieceCell.column] = NULL;
    GamePiece* gamePieceToEat = board->boardData[cellToMoveTo->row][cellToMoveTo->column];
    if(gamePieceToEat!=NULL){
        List* listPieceToEatIsIn = board->gamePieces[PIECES_INDEX(gamePieceToEat->isWhite)][gamePieceToEat->typeOfGamePiece];
        delete_item(listPieceToEatIsIn, get_element_index_using_pointer_to_list_element(listPieceToEatIsIn, pieceToMove));
        
    }
    pieceToMove->gamePieceCell.row = cellToMoveTo->row;
    pieceToMove->gamePieceCell.column=cellToMoveTo->column;
}
