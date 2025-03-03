#include "hclib.h"

#include <stdlib.h>

void print_moves(move_t **moves) {
    for (int i = 0; moves[i] != NULL; i++) {
        printf("Pawn moves from (%d, %d) to (%d, %d)\n", 
               moves[i]->from_i, moves[i]->from_j, 
               moves[i]->to_i, moves[i]->to_j);
    }
}

int main( int argc, char **argv )
{

    printf("\nThis is the A1Test program.\n");
    printf("\nThe point of this program is to test the functions that were created in A1.\n");
    printf("\nBeginning Testing.\n.\n.\n.\n");

    // Sample chessboard with a white pawn at (6, 4) and a black pawn at (1, 4)
    board_t board = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},  // White pawns at row 6
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    // Test for a white pawn at (6, 4)
    int pawn_i = 6, pawn_j = 4;
    move_t **white_pawn_moves = pawn_moves(&board, pawn_i, pawn_j, 0);  // White pawn

    // Print the valid moves
    printf("White pawn moves:\n");
    print_moves(white_pawn_moves);

    // Test for a black pawn at (1, 4)
    pawn_i = 1, pawn_j = 4;
    move_t **black_pawn_moves = pawn_moves(&board, pawn_i, pawn_j, 1);  // Black pawn

    // Print the valid moves
    printf("\nBlack pawn moves:\n");
    print_moves(black_pawn_moves);

    // Free memory for white pawn moves
    for (int i = 0; white_pawn_moves[i] != NULL; i++) {
        free(white_pawn_moves[i]);
    }
    free(white_pawn_moves);

    // Free memory for black pawn moves
    for (int i = 0; black_pawn_moves[i] != NULL; i++) {
        free(black_pawn_moves[i]);
    }
    free(black_pawn_moves);

    return 0;
}
