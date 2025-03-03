//This is the header file for the C library


//Including necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//
//Below are the typedef structures that will be used in the library
//

//Typedef structure "board_t" that represents the playing field board
typedef char board_t[8][8];
//row - rank; 0-7 corresponods to 1-8
//column - file; 0-7 corresponds to a-h

//Typedef structure "exboard_t" that represents the whole board including the playinf field, prisons, and airfields
typedef struct
{
char bprison[16];
char bairfield[16];
board_t board;
char wprison[16];
char wairfield[16];
} exboard_t;

//Typedef structure "move_t" that represents a move action on the board
typedef struct
{
int from_i, from_j;
int to_i, to_j;
char promotion;
char hostage;
} move_t;

//
//Below are the board ultility functions of the C library
//

//This function returns an "exboard_t" structure that has been malloc’ed or NULL if malloc fails.
//The board_t portion of the board should be fully setup with the with the 4 other fields being left empty with a "\0" (NULL) at the first 
//index of the field arrays
exboard_t *newboard();

//This function will return an exboard_t that has been malloc’ed or NULL if malloc fails. The contents of the returned board structure 
//will match those of the passed board. (HINT: memcpy.)
exboard_t *copyboard( exboard_t *board );

//This fuction will return a 162 character long string that represents the entire board in a single string
char *stringboard( exboard_t *board );

//Helper function to apply_move function to remove a character from a null-terminated array and shift elements left
void remove_piece_from_array(char *array, char piece);

//Helper function to apply_move function to add a piece to prison or airfield
void add_piece_to_array(char *array, char piece);

//This function will move a piece on the board from the start position indicated in move to the end position indicated in move. Function assumes move is legal
exboard_t *apply_move( exboard_t *board, move_t *move );

//
//Below are the move functions of the C library
//
//If there are n valid moves, then this function will return an array of n+1 pointers
//Each pointer will point to a move structure. The n+1th element of the array (at index n) will be a NULL pointer
//Malloc each move, as well as the array of moves, so that they can later be freed
//Function will return an array of n+1 pointers
//

//This function shall identify the piece located on the board at position from_i, from_j, and call the appropriate move_ function, returning the result
//returned by the corresponding move_ function
//Functions assumes that there is a valid piece at the given location and that the move_ function’s return value is valid
move_t **moves( board_t *board, int from_i, int from_j );

//This function will be given a valid board containing a knight ( n/N) at location from_i, from_j
//If the knight is white then colour==0, and if the knight is black then colour==1
move_t **knightmoves( board_t *board, int from_i, int from_j, int colour );

//This function will be given a valid board_t containing a bishop ( p/P) at location from_i, from_j
//If the bishop is white then colour==0, and if the bishop is black then colour==1
move_t **bishopmoves( board_t *board_t, int from_i, int from_j, int colour );

//This function will be given a valid board containing a rook ( r/R) at location from_i, from_j
//If the rook is white then colour==0, and if the rook is black then colour==1
//Do not implement castling moves at this time
move_t **rookmoves( board_t *board_t, int from_i, int from_j, int colour );

//This function will be given a valid board containing a queen ( q/Q) at location from_i, from_j
//If the queen is white then colour==0, and if the queen is black then colour==1
//Consider implementing this function by concatenating the bishop and rook moves
move_t **queenmoves( board_t *board_t, int from_i, int from_j, int colour );

//This function will be given a valid board containing a king ( k/K) at location from_i, from_j
//If the king is white then colour==0, and if the king is black then colour==1.
//Do not need to check if a king would move into check
move_t **king_moves( board_t *board_t, int from_i, int from_j, int colour );

//This function will be given a valid board containing a pawn ( p/P) at location from_i, from_j
//If the pawn is white then colour==0, and if the pawn is black then colour==1
//Do not implement en passant at this time
move_t **pawn_moves( board_t *board_t, int from_i, int from_j, int colour );

//This function takes an extended board and produces a fen string with the additional strings appended 
char *fen( exboard_t *board, char *active, char *castling, char *enpassant, int half, int full );

//This function does the opposite of the 'stringboard' funciton
exboard_t *boardstring( char *string );



