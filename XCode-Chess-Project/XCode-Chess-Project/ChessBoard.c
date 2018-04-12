//
//  ChessBoard.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessBoard.h"
#include "GamePieces.h"
#include <ctype.h>
#define WHITE_PAWNS_ROW_INDEX 1
#define BLACK_PAWNS_ROW_INDEX 6
#define WHITE_NON_PAWNS_ROW_INDEX 0
#define BLACK_NON_PAWNS_ROW_INDEX 7
#define NON_PAWN_ROW_INDEX(isWhite) isWhite? 0:7
#define PAWN_ROW_INDEX(isWhite) isWhite ? 1:6
#define IS_CHAR_UPPER_CASE(char) ((char>='A')&&(char<='Z'))
#define BOARD_FILE_BOARD_ROW_LENGTH 20
#define FIX_ROW_FOR_PRINTING_FROM_ZERO_BASED_TO_ONE_BASE(row) (row+1)
#define ROOK_STR "rook"
#define KNIGHT_STR "knight"
#define KING_STR "king"
#define QUEEN_STR "queen"
#define BISHOP_STR "bishop"
#define PAWN_STR "pawn"
#define ROOK_CHAR 'r'
#define KNIGHT_CHAR 'n'
#define BISHOP_CHAR 'b'
#define PAWN_CHAR 'm'
#define QUEEN_CHAR 'q'
#define KING_CHAR 'k'
/**
 THE ARRAY OF THE PIECES AS ORDERED IN CHESS GAME IN THE FIRST ROW FROM THE SIDE OF THE PLAYER
 */
#define FIRST_ROW_OF_PIECES {Rook,Knight,Bishop,Queen,King,Bishop,Knight,Rook}
/**
 fill the board empty spaces with null
 
 @param board the board to fill
 */
static void _fill_board_data_with_null(ChessBoard *board) {
    for (int row = 0; row<BOARD_SIZE; row ++)
    {
        for (int col = 0; col<BOARD_SIZE; col++)
        {
            (board->boardData)[row][col] = NULL;
        }
    }
}



/**
 init pawns for specific color
 
 @param board board of game
 @param isWhite is white boolean
 */
static void _init_pawns_for_color(ChessBoard* board, bool isWhite){
    List* pawnsList = board->gamePieces[PIECES_INDEX(isWhite)][Pawn];
    for (int columnIndex = 0; columnIndex<BOARD_SIZE; columnIndex++)
    {
        
        const int rowIndex =PAWN_ROW_INDEX(isWhite);
        GamePiece* pawn = init_game_piece(Pawn,isWhite,columnIndex,rowIndex);
        insert_item(pawnsList, pawn);
        board->boardData[pawn->gamePieceCell.row][pawn->gamePieceCell.column] = pawn;
        
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
        board->boardData[gamePiece->gamePieceCell.row][gamePiece->gamePieceCell.column] = gamePiece;
        
        
        
    }
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
            board->gamePieces[i][j] = init_list(2,free,copy_game_piece);
        }
    }
}

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
    ChessBoard* board = (ChessBoard *) malloc(sizeof(ChessBoard));
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
        fprintf(f, "%d| %s|\n", (FIX_ROW_FOR_PRINTING_FROM_ZERO_BASED_TO_ONE_BASE(row)), rowData);
        free(rowData);
        
    }
    fprintf(f, "  -----------------\n");
    fprintf(f, "   A B C D E F G H\n");
}



/**
 Gets this game board piece that is associated with the given symbol
 */
GamePiece* _init_game_piece_using_cell(char symbol,Cell* cell) {
    GamePiece* piece = malloc(sizeof(GamePiece));
    
    if(IS_CHAR_UPPER_CASE(symbol)){
        piece->isWhite = false;
    }
    else{
        piece->isWhite = true;
    }
    piece->gamePieceCell = *cell;
    char loweredSymbol = (char)tolower(symbol);
        switch (loweredSymbol) {
            case PAWN_CHAR:
                piece->typeOfGamePiece = Pawn;
                break;
            case BISHOP_CHAR:
                piece->typeOfGamePiece = Bishop;
                break;
            case KNIGHT_CHAR:
                piece->typeOfGamePiece = Knight;
                break;
            case ROOK_CHAR:
                piece->typeOfGamePiece = Rook;
                break;
            case QUEEN_CHAR:
                piece->typeOfGamePiece = Queen;
                break;
            case KING_CHAR:
                piece->typeOfGamePiece = King;
                break;
            default:
                break;
        }
    
   
    return piece;

}

/**
 Inits a new ChessBoard according to the data in boardData. Each cell will hold the gamePiece defiend by its corresponding
 char in boardData. NULL will be set in placed where the char is equal to EMPTY_SLOT_CHAR
 */
ChessBoard* _init_board_from_chars(char boardData[BOARD_SIZE][BOARD_SIZE]) {
    ChessBoard* board = malloc(sizeof(ChessBoard));
    
    _fill_board_data_with_null(board);
    _init_pieces_lists(board);
    for(int rowIndex = 0;rowIndex<BOARD_SIZE;rowIndex++){
        for(int columnIndex = 0;columnIndex<BOARD_SIZE;columnIndex++){
            Cell cell;
            cell.column = columnIndex;
            cell.row = rowIndex;
            if(boardData[rowIndex][columnIndex] != EMPTY_SLOT_CHAR){
            GamePiece* piece = _init_game_piece_using_cell(boardData[rowIndex][columnIndex], &cell);
            board->boardData[piece->gamePieceCell.row][piece->gamePieceCell.column] = piece;
            List* listToInsertPiece = board->gamePieces[PIECES_INDEX(piece->isWhite)][piece->typeOfGamePiece];
            insert_item(listToInsertPiece, piece);
            }
        }
    }
    return board;
}

/**
 Loads a ChessBoard from the given (valid!) file.
 */
ChessBoard* load_board_from_file(FILE* file) {
    
    char boardData[BOARD_SIZE][BOARD_SIZE];
    
    char* currentRow = (char*)malloc(BOARD_FILE_BOARD_ROW_LENGTH+1);
    for (int row = BOARD_SIZE-1; row>=0; row--) {
        
        if (fgets(currentRow, MAX_LINE_LENGTH, file)== NULL) return NULL;
        char* currentCell = strtok(currentRow, " "); // Skip first
        for (int col = 0; col < BOARD_SIZE; col ++) {
            currentCell = strtok(NULL, " ");
            char pieceSymbol = currentCell[0];
            boardData[row][col] = pieceSymbol;
        }
    }
    
    free(currentRow);
    return _init_board_from_chars(boardData);
}
static void _copy_board_game_pieces(ChessBoard *board, int i, int j, ChessBoard *newBoard) {
    List* typedandColoredGamePiecesList = board->gamePieces[i][j];
    List* newList = copy_list(typedandColoredGamePiecesList);;
    newBoard->gamePieces[i][j] = newList;
    for(int gamePieceIndex = 0;gamePieceIndex<(int)get_items_count(typedandColoredGamePiecesList);gamePieceIndex++){
        GamePiece* piece = get_element(newList,gamePieceIndex);
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
 get index of game piece in list

 @param list the list of game pieces where the piece is
 @param gamePieceToFind the game piece to find
 @return index of game piece in list if found,else -1
 */
size_t _get_index_of_game_piece_in_list(List* list,GamePiece* gamePieceToFind){
    for(int i =0;i<(int)get_items_count(list);i++){
        GamePiece* gamePieceInList = get_element(list, i);
        if(gamePieceToFind->gamePieceCell.column == gamePieceInList->gamePieceCell.column && gamePieceToFind->gamePieceCell.row == gamePieceInList->gamePieceCell.row ){
            return i;
        }
    }
    return -1;
}

static void _eat_piece(ChessBoard *board, GamePiece *gamePieceToEat) {
    List* listPieceToEatIsIn = board->gamePieces[PIECES_INDEX(gamePieceToEat->isWhite)][gamePieceToEat->typeOfGamePiece];
    board->boardData[gamePieceToEat->gamePieceCell.row][gamePieceToEat->gamePieceCell.column]=NULL;
    delete_item(listPieceToEatIsIn, _get_index_of_game_piece_in_list( listPieceToEatIsIn, gamePieceToEat));
    free(gamePieceToEat);
}

static void _move_piece(ChessBoard *board, Cell *cellToMoveTo, GamePiece *pieceToMove) {
    board->boardData[pieceToMove->gamePieceCell.row][pieceToMove->gamePieceCell.column] = NULL;
    board->boardData[cellToMoveTo->row][cellToMoveTo->column] = pieceToMove;
    pieceToMove->gamePieceCell.row = cellToMoveTo->row;
    pieceToMove->gamePieceCell.column = cellToMoveTo->column;
}

static void _eat_piece_if_needed(ChessBoard *board, Cell *cellToMoveTo) {
    GamePiece* gamePieceToEat = board->boardData[cellToMoveTo->row][cellToMoveTo->column];
    if(gamePieceToEat!=NULL){
        _eat_piece(board, gamePieceToEat);
    }
}

/**
 make a move on board
 
 @param board board
 @param pieceToMove the piece to move
 @param cellToMoveTo the cell to move to the piece
 */
void make_move_on_board(ChessBoard* board, GamePiece* pieceToMove,Cell* cellToMoveTo){
    _eat_piece_if_needed(board, cellToMoveTo);
    _move_piece(board, cellToMoveTo, pieceToMove);
}



/**
 Returns a string representing the given cells piece, NULL if there is no piece in the given cell
 */
char* get_user_friendly_string_for_piece_in_cell(ChessBoard* board, int row, int col) {
    PieceType type = board->boardData[row][col]->typeOfGamePiece;
    if (type == Rook) return ROOK_STR;
    else if (type == Knight) return KNIGHT_STR;
    else if (type == King) return KING_STR;
    else if (type == Queen) return QUEEN_STR;
    else if (type == Bishop) return BISHOP_STR;
    else if (type == Pawn) return PAWN_STR;
    else return NULL;
}
