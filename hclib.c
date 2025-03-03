#include "hclib.h"

//Function that returns a new board that is fully initialized.
exboard_t *newboard()
{


    //Creating and mallocing exboard_t structure.
    exboard_t *createdBoard = malloc (sizeof(exboard_t));

    if(createdBoard == NULL)
    {
        return NULL;
    }

    //Initializing the board with spaces.
    //Setting all squares on the board to empty.
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            createdBoard->board[i][j] = ' '; 
        }
    }

    //Placing white pieces on index rows 0 and 1.
    createdBoard->board[0][0] = 'R'; //Placed Rook.
    createdBoard->board[0][1] = 'N'; //Placed Knight.
    createdBoard->board[0][2] = 'B'; //Placed Bishop.
    createdBoard->board[0][3] = 'Q'; //Placed Queen.
    createdBoard->board[0][4] = 'K'; //Placed King.
    createdBoard->board[0][5] = 'B'; //Placed Bishop.
    createdBoard->board[0][6] = 'N'; //Placed Knight.
    createdBoard->board[0][7] = 'R'; //Placed Rook.
    for (int j = 0; j < 8; j++) 
    {
        createdBoard->board[1][j] = 'P'; //Placed Pawns.
    }

    //Placing black pieces on index rows 6 and 7.
    createdBoard->board[7][0] = 'r'; //Placed Rook.
    createdBoard->board[7][1] = 'n'; //Placed Knight.
    createdBoard->board[7][2] = 'b'; //Placed Bishop.
    createdBoard->board[7][3] = 'q'; //Placed Queen.
    createdBoard->board[7][4] = 'k'; //Placed King.
    createdBoard->board[7][5] = 'b'; //Placed Bishop.
    createdBoard->board[7][6] = 'n'; //Placed Knight.
    createdBoard->board[7][7] = 'r'; //Placed Rook.

    for (int j = 0; j < 8; j++) 
    {
        createdBoard->board[6][j] = 'p'; //Placed Pawns.
    }

    //Initializing prisons and airfields to empty strings.
    createdBoard->bprison[0] = '\0'; //Null-terminate the black prison.
    createdBoard->bairfield[0] = '\0'; //Null-terminate the black airfield.
    createdBoard->wprison[0] = '\0'; //Null-terminate the white prison.
    createdBoard->wairfield[0] = '\0'; //Null-terminate the white airfield.

    //Returns the newly created board.
    return createdBoard; 

}

//Function that copies a board passed to it and returns a pointer to a new board.
exboard_t *copyboard( exboard_t *board )
{

    //Checking if passed board is not NULL.
    if(board == NULL)
    {
        return NULL;
    }

    //Creating and mallocing exboard_t structure for copied board.
    exboard_t *copiedBoard = malloc (sizeof(exboard_t));

    if(copiedBoard == NULL)
    {
        return NULL;
    }

    //Using memcpy to copy the original board to the new one.
    memcpy(copiedBoard, board, sizeof(exboard_t));

    //Returning the copied board.
    return copiedBoard; 

}

//Function that converts entire extended board to a single 162 character long string.
char *stringboard( exboard_t *board )
{

    //Allocating memory for the string (162 characters)
    char *longString = malloc(162 * sizeof(char));
    
    if (longString == NULL) 
    {
        printf("ERROR");
        return NULL;
    }

    //Fully intalizing longString
    for(int i = 0; i < 162; i++)
    {
        longString[i] = ' ';
    }

    //Putting in newline characters
    for(int i = 8; i < 162; i += 9)
    {
        longString[i] = '\n';
    }

    //Putitng in dashes

    for(int i = 36; i < 44; i++)
    {
        longString[i] = '-';
    }

    for(int i = 117; i < 125; i++)
    {
        longString[i] = '-';
    }

    //Putting in board pieces
    int a = 0 ;
    for(int i = 45; i < 53; i++)
    {
        longString[i] = board->board[7][a];
        a++;
    }

    int b = 0 ;
    for(int i = 54; i < 62; i++)
    {
        longString[i] = board->board[6][b];
        b++;
    }

    int c = 0 ;
    for(int i = 63; i < 71; i++)
    {
        longString[i] = board->board[5][c];
        c++;
    }

    int d = 0 ;
    for(int i = 72; i < 80; i++)
    {
        longString[i] = board->board[4][d];
        d++;
    }

    int e = 0 ;
    for(int i = 81; i < 89; i++)
    {
        longString[i] = board->board[3][e];
        e++;
    }

    int f = 0 ;
    for(int i = 90; i < 98; i++)
    {
        longString[i] = board->board[2][f];
        f++;
    }

    int g = 0 ;
    for(int i = 99; i < 107; i++)
    {
        longString[i] = board->board[1][g];
        g++;
    }

    int h = 0 ;
    for(int i = 108; i < 116; i++)
    {
        longString[i] = board->board[0][h];
        h++;
    }

    //Putting in bprison
    int bprisoni = 0;
    for (int i = 0; i < 17; i ++)
    {
        if (i == 8)
        {
            longString[i] = '\n';
        }
        else
        {
            if(board->bprison[bprisoni] == '\0'){

                break;
            }
            else
            {
                
                longString[i] = board->bprison[bprisoni];
                bprisoni++;
            }
        }
    }

    //Putting in bairfield
    int bairfieldi = 0;
    for (int i = 18; i < 35; i ++)
    {
        if (i == 26)
        {
            longString[i] = '\n';
        }
        else
        {
            if(board->bairfield[bairfieldi] == '\0'){
                
                break;
            }
            else
            {
                
                longString[i] = board->bairfield[bairfieldi];
                bairfieldi++;
            }
        }
    }

    //Putting in wairfield
    int wairfieldi = 0;
    for (int i = 126; i < 143; i ++)
    {
        if (i == 134)
        {
            longString[i] = '\n';
        }
        else
        {
            if(board->wairfield[wairfieldi] == '\0'){
                
                break;
            }
            else
            {
                
                longString[i] = board->wairfield[wairfieldi];
                wairfieldi++;
            }
        }
    }

    //Putting in wprison
    int wprisoni = 0;
    for (int i = 144; i < 161; i ++)
    {
        if (i == 152)
        {
            longString[i] = '\n';
        }
        else
        {
            if(board->wprison[wprisoni] == '\0'){
                
                break;
            }
            else
            {
                 
                longString[i] = board->wprison[wprisoni];
                wprisoni++;
            }
        }
    }

    

    //Ending longString with string end character
    longString[161] = '\0';

    //Returning longString
    return longString;
}

//Helper function to apply_move function to remove a character from a null-terminated array and shift elements left.
void remove_piece_from_array(char *array, char piece) 
{
    int len = strlen(array); 
    for (int i = 0; i < len; i++) {
        if (array[i] == piece) {
            memmove(&array[i], &array[i + 1], len - i);  //memmove commands shifts contents left to remove the gap.
            break;
        }
    }
}

//Helper function to apply_move function to add a piece to prison or airfield.
void add_piece_to_array(char *array, char piece) 
{
    int len = strlen(array);
    if (len < 15) {
        array[len] = piece;
        array[len + 1] = '\0';
    }
}

//Function that applies a move and moves a taken piece to the appropriate prison.
exboard_t *apply_move(exboard_t *board, move_t *move) 
{
    //Determining what the piece is being moved.
    char piece; 

    if (move->from_i >= 0 && move->from_i < 8) 
    {
        piece = board->board[move->from_i][move->from_j];
    } else {
        piece = ' ';
    }

    //Determinging what piece is at the destination.
    char to_piece = board->board[move->to_i][move->to_j];

    //IF statements handles airfield drops (from_i is 8 or -1).
    if (move->from_i == 8 || move->from_i == -1) 
    {
        //Determining target airfield
        char *airfield; 

        if (move->from_i == 8) 
        {
            airfield = board->bairfield;
        } else {
            airfield = board->wairfield;
        }

        //Removing the promotion piece from the airfield and shift elements left.
        remove_piece_from_array(airfield, move->promotion);
        //Places the piece on the target position.
        board->board[move->to_i][move->to_j] = move->promotion;
        return board;
    }

    //IF statements handles prison drops (from_i is 9 or -2).
    if (move->from_i == 9 || move->from_i == -2) 
    {
        //Determining target prison.
        char *prison;  

        if (move->from_i == 9) 
        {
            prison = board->bprison;
        } else {
            prison = board->wprison;
        }

        //Determining target opponent prison.
        char *opponent_prison; 

        if (move->from_i == 9) 
        {
            opponent_prison = board->wprison;
        } else {
            opponent_prison = board->bprison;
        }

        //Determining target airfield.
        char *airfield;  

        if (move->from_i == 9) 
        {
            airfield = board->bairfield;
        } else {
            airfield = board->wairfield;
        }

        //Calls helper function to remove the promotion piece from the prison and shift elements left.
        remove_piece_from_array(prison, move->promotion);
        // Place the piece on the target position
        board->board[move->to_i][move->to_j] = move->promotion;

        //Calls helper function to remove the hostage piece from the opponent's prison and shift elements left.
        remove_piece_from_array(opponent_prison, move->hostage);
        // Add the hostage piece to the current player's airfield
        add_piece_to_array(airfield, move->hostage);
        return board;
    }

    //IF statement handles castling (king moves more than one space left or right).
    if ((piece == 'K' || piece == 'k') && abs(move->to_j - move->from_j) > 1) 
    {
        //Moving the rook to the other side of the king.
        int rook_j;
        int newRook_j;

        if (move->to_j > move->from_j) 
        {
            rook_j = move->to_j + 1;
        } 
        else 
        {
            rook_j = move->to_j - 1;
        }

        if (move->to_j > move->from_j) 
        {
            newRook_j = move->to_j - 1;
        } 
        else 
        {
            newRook_j = move->to_j + 1;
        }

        board->board[move->to_i][newRook_j] = board->board[move->to_i][rook_j];  //Moving the rook.
        board->board[move->to_i][rook_j] = ' ';  //Clearing the old rook position to a blank.
    }

    //IF statement handles en passant (pawn moves diagonally to an empty square).
    if ((piece == 'P' || piece == 'p') && to_piece == ' ' && abs(move->from_j - move->to_j) == 1) 
    {
        //Remove the captured pawn.
        int capturedPawn_i;  // Declare the variable

        if (piece == 'P') {
            capturedPawn_i = move->to_i - 1;
        } else {
            capturedPawn_i = move->to_i + 1;
        }
        to_piece = board->board[capturedPawn_i][move->to_j];  //Assign captured pawn to to_piece variable
        board->board[capturedPawn_i][move->to_j] = ' ';  //Remove it from the board
    }

    //Adding captured piece to the opponent's prison if applicable.
    if (to_piece != ' ') 
    {
        if (to_piece >= 'A' && to_piece <= 'Z') {
            // White piece captured, add to black prison
            add_piece_to_array(board->bprison, to_piece);
        } else {
            // Black piece captured, add to white prison
            add_piece_to_array(board->wprison, to_piece);
        }
    }

    //Move the piece to the new position.
    board->board[move->to_i][move->to_j] = (move->promotion != ' ') ? move->promotion : piece;

    //Clearing the starting position.
    if (move->from_i >= 0 && move->from_i < 8) {
        board->board[move->from_i][move->from_j] = ' ';
    }

    //Returns board with move applied.
    return board;
}

//Moves function that calls a specific move function based on the detected piece at the "from" location.
move_t **moves( board_t *board, int from_i, int from_j )
{
    //Identifying the piece at the given position.
    char piece = (*board)[from_i][from_j];

    printf("\n%c\n",piece);

    int colour = (piece >= 'a' && piece <= 'z') ? 1 : 0;  // Determine colour (lowercase = black, uppercase = white)
    move_t **possible_moves = NULL;

    switch (piece)
    {
        case 'n': case 'N':
            possible_moves = knightmoves(board, from_i, from_j, colour);
            break;
        case 'b': case 'B':
            possible_moves = bishopmoves(board, from_i, from_j, colour);
            break;
        case 'r': case 'R':
            possible_moves = rookmoves(board, from_i, from_j, colour);
            break;
        case 'q': case 'Q':
            possible_moves = queenmoves(board, from_i, from_j, colour);
            break;
        case 'k': case 'K':
            possible_moves = king_moves(board, from_i, from_j, colour);
            break;
        case 'p': case 'P':
            possible_moves = pawn_moves(board, from_i, from_j, colour);
            break;
        default:
            printf("Unknown piece at position (%d, %d)\n", from_i, from_j);
            break;
    }
    
    return possible_moves;

}


//Knight piece move function.
move_t **knightmoves(board_t *board, int from_i, int from_j, int colour)
{
    // Possible knight move offsets
    int knight_offsets[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    // Maximum possible moves is 8, so we malloc space for 9 pointers (8 + 1 for NULL terminator)
    int max_moves = 8;
    move_t **moves = malloc((max_moves + 1) * sizeof(move_t *));
    int move_count = 0;

    for (int k = 0; k < 8; k++) {
        int to_i = from_i + knight_offsets[k][0];
        int to_j = from_j + knight_offsets[k][1];

        // Ensure the move stays within the board limits
        if (to_i >= 0 && to_i < 8 && to_j >= 0 && to_j < 8) {
            char target_square = (*board)[to_i][to_j];

            // Check if the target square is empty or contains an opponent's piece
            if (target_square == ' ' || 
                (colour == 0 && target_square >= 'a' && target_square <= 'z') ||  // White knight can move to black pieces
                (colour == 1 && target_square >= 'A' && target_square <= 'Z')) {  // Black knight can move to white pieces
                
                // Allocate memory for a new move
                move_t *move = malloc(sizeof(move_t));
                move->from_i = from_i;
                move->from_j = from_j;
                move->to_i = to_i;
                move->to_j = to_j;
                
                // Add the move to the array
                moves[move_count++] = move;
            }
        }
    }

    // Realloc the array to the correct size, move_count + 1 (for NULL terminator)
    moves = realloc(moves, (move_count + 1) * sizeof(move_t *));
    moves[move_count] = NULL;  // Null-terminate the array of moves

    return moves;
}

//Bishop piece move function.
move_t **bishopmoves(board_t *board, int from_i, int from_j, int colour)
{
    // Creating 2D array of all possible directions the bishop can move (diagonal directions).
    int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    int validMoveCount = 0;
    int is_white = (colour == 0);  // If white, check for lowercase enemy pieces
    move_t **moves = malloc(33 * sizeof(move_t*));  // Maximum 32 moves + 1 for NULL pointer

    if (moves == NULL) {
        return NULL;
    }

    // Looping through all four diagonal directions.
    for (int d = 0; d < 4; d++) {
        int step = 1;  // Tracking how far the bishop has moved in this direction.
        while (1) {
            int new_i = from_i + step * directions[d][0];
            int new_j = from_j + step * directions[d][1];

            // Checking if the new position is within the board boundaries.
            if (new_i < 0 || new_i >= 8 || new_j < 0 || new_j >= 8) {
                break;  // Move is out of bounds, stop moving in this direction.
            }

            char target_piece = (*board)[new_i][new_j];

            // Checking if the square is empty or contains an opponent's piece.
            if (target_piece == ' ') {
                // Empty square: valid move
                moves[validMoveCount] = malloc(sizeof(move_t));
                moves[validMoveCount]->from_i = from_i;
                moves[validMoveCount]->from_j = from_j;
                moves[validMoveCount]->to_i = new_i;
                moves[validMoveCount]->to_j = new_j;
                validMoveCount++;
            }
            else if ((is_white && target_piece >= 'a' && target_piece <= 'z') ||  // White bishop can capture black pieces
                     (!is_white && target_piece >= 'A' && target_piece <= 'Z')) { // Black bishop can capture white pieces
                // Opponent's piece: valid move, but stop further movement.
                moves[validMoveCount] = malloc(sizeof(move_t));
                moves[validMoveCount]->from_i = from_i;
                moves[validMoveCount]->from_j = from_j;
                moves[validMoveCount]->to_i = new_i;
                moves[validMoveCount]->to_j = new_j;
                validMoveCount++;
                break;  // Stop this direction after capturing.
            }
            else {
                // Friendly piece at this position: invalid move, stop in this direction.
                break;
            }
            step++;
        }
    }

    // Resize the moves array to fit exactly validMoveCount + 1 elements.
    moves = realloc(moves, (validMoveCount + 1) * sizeof(move_t*));
    moves[validMoveCount] = NULL;  // Null-terminate the list

    return moves;
}

//Rook piece move function.
move_t **rookmoves( board_t *board, int from_i, int from_j, int colour )
{
 int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; 
    int validMoveCount = 0;
    move_t **moves = malloc(65 * sizeof(move_t*));

    if(moves == NULL)
    {
        return NULL;
    }
    
    int is_white = (colour == 0);  

    for (int d = 0; d < 4; d++) 
    {
        int step = 1; 
        while (1) 
        {
            int new_i = from_i + step * directions[d][0];
            int new_j = from_j + step * directions[d][1];

            if (new_i < 0 || new_i >= 8 || new_j < 0 || new_j >= 8) 
            {
                break;  
            }

            char target_piece = (*board)[new_i][new_j];

            if (target_piece == ' ') 
            {
                //Empty square: valid move
                moves[validMoveCount] = malloc(sizeof(move_t));
                moves[validMoveCount]->from_i = from_i;
                moves[validMoveCount]->from_j = from_j;
                moves[validMoveCount]->to_i = new_i;
                moves[validMoveCount]->to_j = new_j;
                moves[validMoveCount]->promotion = ' '; 
                moves[validMoveCount]->hostage = ' ';  
                validMoveCount++;
            } 
            else if ((is_white && target_piece >= 'a' && target_piece <= 'z') || (!is_white && target_piece >= 'A' && target_piece <= 'Z')) 
            {
                moves[validMoveCount] = malloc(sizeof(move_t));
                moves[validMoveCount]->from_i = from_i;
                moves[validMoveCount]->from_j = from_j;
                moves[validMoveCount]->to_i = new_i;
                moves[validMoveCount]->to_j = new_j;
                moves[validMoveCount]->promotion = ' ';
                moves[validMoveCount]->hostage = ' ';
                validMoveCount++;
                break;  
            } 
            else 
            {
                
                break;
            }
            step++;
        }
    }

    moves = realloc(moves, (validMoveCount + 1) * sizeof(move_t*));
    moves[validMoveCount] = NULL; // Null-terminate the list

    return moves;
}

//Queen piece move function.
move_t **queenmoves( board_t *board, int from_i, int from_j, int colour )
{
    //Get the rook moves and bishop move pointer arrays.
    move_t **rookMoves = rookmoves(board, from_i, from_j, colour);
    move_t **bishopMoves = bishopmoves(board, from_i, from_j, colour);

    //Counting the number of rook moves.
    int rookMoveCount = 0;
    while (rookMoves[rookMoveCount] != NULL)
    {
        rookMoveCount++;
    }

    //Counting the number of bishop moves.
    int bishopMoveCount = 0;
    while (bishopMoves[bishopMoveCount] != NULL) 
    {
        bishopMoveCount++;
    }

    //Allocating space for the combined move list.
    move_t **queenMoves = malloc((rookMoveCount + bishopMoveCount + 1) * sizeof(move_t*));

    if(queenMoves == NULL)
    {
        return NULL;
    }

    //Copying rook moves into the queen moves list.
    for (int i = 0; i < rookMoveCount; i++) 
    {
        queenMoves[i] = rookMoves[i];
    }

    // Copying bishop moves into the queen moves list.
    for (int i = 0; i < bishopMoveCount; i++) 
    {
        queenMoves[rookMoveCount + i] = bishopMoves[i];
    }

    //Adding the NULL pointer at the end.
    queenMoves[rookMoveCount + bishopMoveCount] = NULL;

    //Freeing the original arrays of bishop and rook moves called at the start to prevent memory leaks.
    free(rookMoves);
    free(bishopMoves);

    return queenMoves;

}

//King piece move function
move_t **king_moves(board_t *board, int from_i, int from_j, int colour) {
    //Creating 2D array of all possible directions the king can move (8 possible moves unchecked).
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, //Up-Left, Up, Up-Right
        {0, -1},           {0, 1},   //Left,       , Right
        {1, -1}, {1, 0}, {1, 1}      //Down-Left, Down, Down-Right
    };

    //Initial malloc allocation for potential moves pointer array.
    move_t **moves = malloc(9 * sizeof(move_t*)); // Allocating space for 8 moves + NULL.

    if (moves == NULL) {
        return NULL;
    }

    int validMoveCount = 0;

    //Looping through all possible moves.
    for (int d = 0; d < 8; d++) {
        int new_i = from_i + directions[d][0];
        int new_j = from_j + directions[d][1];

        //Checking if the new position is within the board boundaries.
        if (new_i >= 0 && new_i < 8 && new_j >= 0 && new_j < 8) {
            char targetPiece = (*board)[new_i][new_j];

            //Check if the target square is empty or occupied by an opponent's piece.
            if (targetPiece == ' ' || (colour == 1 && targetPiece >= 'a' && targetPiece <= 'z') || (colour == 0 && targetPiece >= 'A' && targetPiece <= 'Z')) {
                //Creating a new move structure.
                moves[validMoveCount] = malloc(sizeof(move_t));
                moves[validMoveCount]->from_i = from_i;
                moves[validMoveCount]->from_j = from_j;
                moves[validMoveCount]->to_i = new_i;
                moves[validMoveCount]->to_j = new_j;
                moves[validMoveCount]->promotion = ' '; //Assuming no promotion status for kings
                moves[validMoveCount]->hostage = ' ';   //Assuming no hostage status for kings
                validMoveCount++;
            }
        }
    }

    //Resizing the pointer array to fit the number of valid moves using realloc and adding NULL terminator.
    moves = realloc(moves, (validMoveCount + 1) * sizeof(move_t*));
    moves[validMoveCount] = NULL; //NULL pointer terminating the array.

    return moves; //Return the array of valid moves
}

//Pawn piece move function.
move_t **pawn_moves(board_t *board, int from_i, int from_j, int colour) {
    move_t **moves = malloc(5 * sizeof(move_t*)); 
    int validMoveCount = 0;
    
    int direction;
    int start_row;
    
    if (colour == 0) { 
        direction = -1;  //White pawns move up (negative direction)
        start_row = 6;   //White pawns start at row 6
    } else { 
        direction = 1;   //Black pawns move down (positive direction)
        start_row = 1;   //Black pawns start at row 1
    }

    //Check the square directly in front of the pawn (moving one square forward)
    if ((*board)[from_i + direction][from_j] == ' ') {
        moves[validMoveCount] = malloc(sizeof(move_t));
        moves[validMoveCount]->from_i = from_i;
        moves[validMoveCount]->from_j = from_j;
        moves[validMoveCount]->to_i = from_i + direction;
        moves[validMoveCount]->to_j = from_j;
        moves[validMoveCount]->promotion = ' ';
        moves[validMoveCount]->hostage = ' ';
        validMoveCount++;

        //If the pawn is in its starting row and both squares directly ahead are empty, it can move 2 squares
        if (from_i == start_row && (*board)[from_i + 2 * direction][from_j] == ' ') {
            moves[validMoveCount] = malloc(sizeof(move_t));
            moves[validMoveCount]->from_i = from_i;
            moves[validMoveCount]->from_j = from_j;
            moves[validMoveCount]->to_i = from_i + 2 * direction;
            moves[validMoveCount]->to_j = from_j;
            moves[validMoveCount]->promotion = ' ';
            moves[validMoveCount]->hostage = ' ';
            validMoveCount++;
        }
    }

    //Check diagonals for capturing opponent's piece
    for (int offset = -1; offset <= 1; offset += 2) { 
        int new_j = from_j + offset;
        if (new_j >= 0 && new_j < 8) { 
            char target_piece = (*board)[from_i + direction][new_j];
            if (colour == 0) {  //White pawn
                if (target_piece >= 'a' && target_piece <= 'z') { 
                    moves[validMoveCount] = malloc(sizeof(move_t));
                    moves[validMoveCount]->from_i = from_i;
                    moves[validMoveCount]->from_j = from_j;
                    moves[validMoveCount]->to_i = from_i + direction;
                    moves[validMoveCount]->to_j = new_j;
                    moves[validMoveCount]->promotion = ' ';
                    moves[validMoveCount]->hostage = ' ';
                    validMoveCount++;
                }
            } else {  //Black pawn
                if (target_piece >= 'A' && target_piece <= 'Z') { 
                    moves[validMoveCount] = malloc(sizeof(move_t));
                    moves[validMoveCount]->from_i = from_i;
                    moves[validMoveCount]->from_j = from_j;
                    moves[validMoveCount]->to_i = from_i + direction;
                    moves[validMoveCount]->to_j = new_j;
                    moves[validMoveCount]->promotion = ' ';
                    moves[validMoveCount]->hostage = ' ';
                    validMoveCount++;
                }
            }
        }
    }

    //Resize the moves array to fit the number of valid moves and add NULL terminator
    moves = realloc(moves, (validMoveCount + 1) * sizeof(move_t*));
    moves[validMoveCount] = NULL; 

    return moves;
}

//This function takes an extended board and produces a fen string with the additional strings appended 
char *fen( exboard_t *board, char *active, char *castling, char *enpassant, int half, int full )
{
    char *fenString = malloc(65 * sizeof(char));

    if (fenString == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 65; i++)
    {
        fenString [i] = '0';
    }

    int currentFENStringIndex = 0;
    int empty = 0;

    for(int row = 0; row < 8; row++)
    {
        
        for (int column = 0; column < 8; column++)
        {
            char piece = board->board[row][column];
            if(piece == ' ')
            {
                empty++;
            }

            else
            {
                if (empty > 0) {
                    currentFENStringIndex += sprintf(fenString + currentFENStringIndex, "%d", empty);
                    empty = 0;
                }

                fenString[currentFENStringIndex++] = piece;
            }
            
        }

        if (empty > 0) 
        {
            currentFENStringIndex += sprintf(fenString + currentFENStringIndex, "%d", empty);
            empty = 0;
        }

        if (row < 7) 
        {
            fenString[currentFENStringIndex++] = '/';
        }
        
    }

    fenString[currentFENStringIndex] = '\0'; // Null-terminate the string

    printf("\n%s\n", fenString);

    char *finalFENString = realloc(fenString, (currentFENStringIndex + 1) * sizeof(char));

    if(finalFENString == NULL)
    {
        return NULL;
    }

    return finalFENString;

}

//This function does the opposite of the 'stringboard' funciton
exboard_t *boardstring( char *string )
{

    exboard_t *createdBoard = malloc (sizeof(exboard_t));

    if(createdBoard == NULL)
    {
        return NULL;
    }


    int bprisonIndex = 0;
    int bairfieldIndex = 0;
    int rowOneIndex = 0;
    int rowTwoIndex = 0;
    int rowThreeIndex = 0;
    int rowFourIndex = 0;
    int rowFiveIndex = 0;
    int rowSixIndex = 0;
    int rowSevenIndex = 0;
    int rowEightIndex = 0;
    int wprisonIndex = 0;
    int wairfieldIndex = 0;

    for(int currentIndex = 0; currentIndex < 162; currentIndex++)
    {
        

        //bprison
        if ((currentIndex >= 0 && currentIndex <= 7) || (currentIndex >= 9 && currentIndex <= 16) )
        {
            if(string[currentIndex] == ' '){
                createdBoard->bprison[bprisonIndex] = '\0';
                
            }
            else{
                createdBoard->bprison[bprisonIndex] = string[currentIndex];
                bprisonIndex++;
            }
        }

        //bairfield
        else if ((currentIndex >= 18 && currentIndex <= 25) || (currentIndex >= 27 && currentIndex <= 34) )
        {
            if(string[currentIndex] == ' '){
                createdBoard->bairfield[bairfieldIndex] = '\0';
                
            }
            else{
                createdBoard->bairfield[bairfieldIndex] = string[currentIndex];
                bairfieldIndex++;
            }
        }

    //8th row
        else if (currentIndex >= 45 && currentIndex <= 52)
        {
            createdBoard->board[7][rowEightIndex] = string[currentIndex];
            rowEightIndex++;
        }

        //7th row
        else if (currentIndex >= 54 && currentIndex <= 61)
        {
            createdBoard->board[6][rowSevenIndex] = string[currentIndex];
            rowSevenIndex++;
        }

        //6th row
        else if (currentIndex >= 63 && currentIndex <= 70)
        {
            createdBoard->board[5][rowSixIndex] = string[currentIndex];
            rowSixIndex++;
        }

        //5th row
        else if (currentIndex >= 72 && currentIndex <= 79)
        {
            createdBoard->board[4][rowFiveIndex] = string[currentIndex];
            rowFiveIndex++;
        }

        //4th row
        else if (currentIndex >= 81 && currentIndex <= 88)
        {
            createdBoard->board[3][rowFourIndex] = string[currentIndex];
            rowFourIndex++;
        }

        //3th row
        else if (currentIndex >= 90 && currentIndex <= 97)
        {
            createdBoard->board[2][rowThreeIndex] = string[currentIndex];
            rowThreeIndex++;
        }

        //2th row
        else if (currentIndex >= 99 && currentIndex <= 106)
        {
            createdBoard->board[1][rowTwoIndex] = string[currentIndex];
            rowTwoIndex++;
        }

        //1th row
        else if (currentIndex >= 108 && currentIndex <= 115)
        {
            createdBoard->board[0][rowOneIndex] = string[currentIndex];
            rowOneIndex++;
        }


        //wairfield
        else if ((currentIndex >= 126 && currentIndex <= 133) || (currentIndex >= 135 && currentIndex <= 142) )
        {
            if(string[currentIndex] == ' '){
                createdBoard->wairfield[wairfieldIndex] = '\0';
            }
            else{
                createdBoard->wairfield[wairfieldIndex] = string[currentIndex];
                wairfieldIndex++;
            }
        }

        //wprison
        else if ((currentIndex >= 144 && currentIndex <= 151) || (currentIndex >= 153 && currentIndex <= 160))
        {
            if(string[currentIndex] == ' '){
                createdBoard->wprison[wprisonIndex] = '\0';
            }
            else{
                createdBoard->wprison[wprisonIndex] = string[currentIndex];
                wprisonIndex++;
            }
        }

        else
        {

        }

    }

    return createdBoard;

}

