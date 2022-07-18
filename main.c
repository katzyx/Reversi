#include <stdio.h>

// Katherine Zhang 1006837292

// This program sets up the board for Reversi game

/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * Katherine Zhang *
 * Date: April 9 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line

// Note: You may want to add more function declarations here
// ========================   Function declaration  ===========================
void initializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n) ;
void boardConfig(char board[][26], char colour, char row, char col, int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
int findAvailableMoves (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool availableMoves(char board[][26], int n, char colour);
bool validMove(char board[][26], int n, char row, char col, char colour);
void checkFilpTiles (char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
void flipTiles(char board[][26], int n, char row, char col, char colour);

// ========================   Function implementation =========================

/* Function:  initializeBoard
 * 
 * Print U for unoccupied and place intial pieces on the board
 */
void initializeBoard(char board[][26], int n)
{
    int i, j;
    
    // first print U for every position
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            board[i][j] = 'U';
    }
    
    // place B and W on middle diagonally
    board[(n / 2) - 1][(n / 2) - 1] = 'W';
    board[n / 2][n / 2] = 'W';
    board[(n / 2) - 1][n / 2] = 'B';
    board[n / 2][(n / 2) - 1] = 'B';
    
} 


/*
 * Function:  printBoard 
 * 
 * Print the whole board to the terminal window.
 * Takes board dimension (boardDim)
 */
void printBoard(char board[][26], int n) 
{
    //char occupied;
    char colLabel = 'a';
    char rowLabel = 'a';
    int i, j, k;
    
    // print the column labels according to board size
    printf("  ");
    for (i = 0; i < n; i++)
    {
        printf("%c", colLabel);
        colLabel++;
    }
    
    // print row labels and board according to board size and letter
    for (j = 0; j < n; j++)
    {
        printf("\n%c ", rowLabel);
        rowLabel++;
        
        for (k = 0; k < n; k++)
            printf("%c", board[j][k]);
    }
    
    printf("\n");

}   

 
/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) 
{
    bool valid;
    
    // if position is out of bounds, return false
    if (row < 0 || row > n || col < 0 || col > n)
        valid = false;
    else
        valid = true;
        
    return valid;
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) 
{
    char opponent;
    int i, j;

    // determine which colour is the opponent
    if (colour == 'W')
        opponent = 'B';
    else
        opponent = 'W';
    
    // starting at position, go through tile in that direction until over boundaries
    for (i = row, j = col; 0 <= i && i < n && 0 <= j && j < n; i += deltaRow, j += deltaCol)
    {
        // if position adjacent is same opposite, continue checking
        if (board[row + deltaRow][col + deltaCol] == opponent)
        {
            if ((i + deltaRow) < 0 || (j + deltaCol) < 0)
                return false;
            // if next position is the same colour, position is valid
            else if (board[i + deltaRow][j + deltaCol] == colour)
                return true;
            // if no colour
            else if (board[i + deltaRow][j + deltaCol] == 'U')
                return false;
            // if still opponent colour, go thorugh loop again
        }
    }
    
    return false;
}


/*
 * Function:  findAvailableMoves 
 * --------------------
 * find position where a piece can be placed
 */
int findAvailableMoves (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) 
{
    char opponent;
    int i, j;

    // determine which colour is the opponent
    if (colour == 'W')
        opponent = 'B';
    else
        opponent = 'W';
    
    // starting at position, go through tile in that direction until over boundaries
    for (i = row, j = col; 0 <= i && i < n && 0 <= j && j < n; i += deltaRow, j += deltaCol)
    {
        
        // if position adjacent is oppponent colour, continue checking
        if (board[row + deltaRow][col + deltaCol] == opponent)
        {
            // if next position is the same colour, position is valid
            if (board[i + deltaRow][j + deltaCol] == colour && (0 <= (i + deltaRow) && (i + deltaRow) < n && 0 <= (j + deltaCol) && (j + deltaCol) < n))
            {
                // convert index to row and col
                char rowLetter = row + 97;
                char colLetter = col + 97;
                    
                printf("%c%c\n", rowLetter, colLetter);
                return 0;
            }
            // if no colour
            else if (board[i + deltaRow][j + deltaCol] == 'U')
                return 0;
            // if still opponent colour, go thorugh loop again
        }
    }
    return 0;
} 

/*
 * Function:  availableMoves 
 * --------------------
 * Finds available moves for a colour and prints them
 */
bool availableMoves(char board[][26], int n, char colour)
{
    int i, j;
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            //convert i and j index to letter
            char iLetter = i + 97;
            char jLetter = j + 97;
            
            if (validMove(board, n, iLetter, jLetter, colour))
                return true;
        }
    }
    
    return false;
}

/*
 * Function:  validMove 
 * --------------------
 * determine if move is valid by calling check funcion
 */
bool validMove(char board[][26], int n, char row, char col, char colour)
{
    // convert char row and col to int index
    int rowIndex = row - 97;
    int colIndex = col - 97;
    
    if (board[rowIndex][colIndex] == 'U')
    {
        
        // check if move is valid by calling function for 8 directions
        if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, 1, -1))
            return true;
        else if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, 1, 0))
            return true;
        else if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, 1, 1))
            return true;
        else if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, 0, -1))
            return true;
        else if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, 0, 1))
            return true;
        else if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, -1, -1))
            return true;
        else if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, -1, 0))
            return true;
        else if (checkLegalInDirection(board, n, rowIndex, colIndex, colour, -1, 1))
            return true;
        else
            return false;
    }
    else
        return false;

}

/*
 * Function:  checkFlipTiles 
 * --------------------
 * function will check if it can flip the tile in direction
 */
 
void checkFilpTiles (char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{
    // convert row and col to index
    int rowIndex = row - 97;
    int colIndex = col - 97;
   
    char opponent;
   
    int i;
   
    // determines opponent colour
    if (colour == 'B')
        opponent = 'W';
    else
        opponent = 'B';

    // check if piece is in position
    if(board[rowIndex][colIndex] == 'U')
    {
        // check if the move is valid
        if(checkLegalInDirection(board, n, rowIndex, colIndex, colour, deltaRow, deltaCol) == true)
        {
            
            // flips every opponent colour until piece of the same colour
            for(i = 1; ; i++)
            {
                if(board[rowIndex + deltaRow * i][colIndex + deltaCol * i] == opponent)
                    board[rowIndex + deltaRow * i][colIndex + deltaCol * i] = colour;
                    
                else if (board[rowIndex + deltaRow * i][colIndex + deltaCol * i] == colour)
                    // cannot flip anymore
                    return;
            }
        }
        else
            return;
    }
    
    return;
}

void flipTiles(char board[][26], int n, char row, char col, char colour)
{
    // check if it can flip tiles then flips
    checkFilpTiles(board, n, row, col, colour, 1, -1);
    checkFilpTiles(board, n, row, col, colour, 1, 0);
    checkFilpTiles(board, n, row, col, colour, 1, 1);
    checkFilpTiles(board, n, row, col, colour, 0, -1);
    checkFilpTiles(board, n, row, col, colour, 0, 1);
    checkFilpTiles(board, n, row, col, colour, -1, -1);
    checkFilpTiles(board, n, row, col, colour, -1, 0);
    checkFilpTiles(board, n, row, col, colour, -1, 1);   
}

int calculateScore(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int score = 0;
    char opponent;
    
    int k;
    
    // determine which colour is the opponent
    if (colour == 'W')
        opponent = 'B';
    else
        opponent = 'W';
 
    // if there is no tile in place and move is legal
    if (board[row][col] == 'U' && checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol))
    {
        for (k = 1; ; k++)
        {
            if (board[row + deltaRow * k][col + deltaCol * k] == opponent)
                score++;
            else if (board[row + deltaRow * k][col + deltaCol * k] == colour)
                return score;
        }
    }
    
    return 0;
}

int countScore(char board[][26], int n, int row, int col, char colour)
{
    int score = 0;
    score = calculateScore(board, n, row, col, colour, -1, -1) +
            calculateScore(board, n, row, col, colour, -1, 0)  +
            calculateScore(board, n, row, col, colour, -1, 1)  +
            calculateScore(board, n, row, col, colour, 0, -1)  +
            calculateScore(board, n, row, col, colour, 0, 1)   +
            calculateScore(board, n, row, col, colour, 1, -1)  +
            calculateScore(board, n, row, col, colour, 1, 0)   +
            calculateScore(board, n, row, col, colour, 1, 1)   ;
    
    return score;
}

/*
 * Function:  makeMove  ////// FOR LAB 8 ONLY /////
 * --------------------
 * The player "turn" makes a move at (row, col). and 
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 * function should calculate a best move for that color
 * location of the best move should return using the two pointers (row and col) to two integer values
 */

int makeMove(const char board[26][26], int n, char turn, int *row, int *col) 
{
    // declaring local variables
    int i, j;
    int score = 0;
    int maxScore = 0;
    
    // calculate score for each tile if it is a valid move
    for(i = 0; i < n; i++) 
    {
        for(j = 0; j < n; j++) 
        {
            // convert index to row and col
            char iLetter = i + 97;
            char jLetter = j + 97;
            
            if  (board[i][j] == 'U' && validMove(board, n, iLetter, jLetter, turn))
            {
                score = countScore(board, n, i, j, turn);
                
                // weighted score based on position the tile can be placed
                // 4 corners
                if ((i == 0 || i == n) && (j == 0 || j == n))
                    score = score * 10;
                
                // sidelines
                else if(i == 0 || i == 1 || j == 0 || j == 1)
                    score = score * 5;
                    
                // sides
                else if(i == 1 || i == n - 1 || j == 1 || j == n - 1)
                    score = score * 3;
               
                else
                    score = score * 1;
                
                // set new max score and the row and col where the tile is
                if(score > maxScore) 
                {
                    maxScore = score;
                    *row = i;
                    *col = j;
                }
            }
        }
    }
    
    // convert index to row and col
    char rowLetterPoint = *row + 97;
    char colLetterPoint = *col + 97;
    
    //printf("Computer places %c at %c%c.\n", turn, rowLetterPoint, colLetterPoint);

    
    return 0;
}


char winner(char board[][26], int n, char playerColour, char compColour) 
{
    int playerTiles = 0;
    int compTiles = 0;
    char winner;
    
    int i, j;
    
    // counts number of tiles for player and comp
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n ; j++) 
        {
            if (board[i][j] == playerColour) 
               playerTiles++;

            else if (board[i][j] == compColour)
               compTiles++;
        }
    }
    
    // compare number of tiles
    if (playerTiles > compTiles)
        winner = playerColour;
        
    else if (compTiles > playerTiles)
       winner = compColour;
       
    else if (compTiles == playerTiles)
        winner = 'U';

    return winner;
}


#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE

//////////////////////////// MAIN FUNCTION ///////////////////////////////
int main(void) 
{
    // Define variables
    int boardDim;
    char board[26][26];
    char compColour;
    char playerColour;
    int row;
    int col;
    char userRow;
    char userCol;
    
    int rowIndex;
    int colIndex;
    
    // Ask for board dimension
    printf("Enter the board dimension: ");
    scanf("%d", &boardDim);
    
    // Ask user if computer is black or white
    printf("Computer plays (B/W) : ");
    scanf(" %c", &compColour);
    
    // intialize and print board
    initializeBoard(board, boardDim);
    printBoard(board, boardDim);
    
    // assigning the turns, if comp = B comp goes first
    if (compColour == 'W') 
        playerColour = 'B';
    else
    {
        playerColour = 'W';
        makeMove(board, boardDim, compColour, &row, &col);
        
        // convert index to row and col
        char rowLetter = row + 97;
        char colLetter = col + 97;
        
        // place tile in position and flip tiles in direction then print
        flipTiles(board, boardDim, rowLetter, colLetter, compColour);
        board[row][col] = compColour; 
        printBoard(board, boardDim);
    }
    
    
    // while player or comp has available moves, take turns
    while (availableMoves(board, boardDim, playerColour) || availableMoves(board, boardDim, compColour))
    {
        // if player has available move, player goes
        if (availableMoves(board, boardDim, playerColour))
        {
            printf("Enter move for colour %c (RowCol): ", playerColour);
            scanf(" %c%c", &userRow, &userCol);
            
            //printf("\nplayer enters: %c %c\n", userRow, userCol);
            
            // convert char row and col to int index
            rowIndex = userRow - 97;
            colIndex = userCol - 97;
        
            // check if move is valid
            if (validMove(board, boardDim, userRow, userCol, playerColour) && positionInBounds(boardDim, rowIndex, colIndex))
            {
                // flip the tiles
                flipTiles(board, boardDim, userRow, userCol, playerColour);
    
                // position piece in row and col
                board[rowIndex][colIndex] = playerColour;
                
                // print board
                printBoard(board, boardDim);
            }
        
            // if not, comp wins
            else
            {
                printf("Invalid move.\n");
                printf("%c player wins.", compColour);
                return 0;
            }
        }
        
        //if comp has available moves but player doesnt, change turn after message
        else if (availableMoves(board, boardDim, compColour))
        {
            printf("%c player has no valid move.\n", playerColour);
        }
        
        // if comp has available moves and player finished turn,
        if (availableMoves(board, boardDim, compColour))
        {
            makeMove(board, boardDim, compColour, &row, &col);
            
            // convert index to row and col
            char rowLetter = row + 97;
            char colLetter = col + 97;
        
            // place tile in position and flip tiles in direction then print
            flipTiles(board, boardDim, rowLetter, colLetter, compColour);
            board[row][col] = compColour; 
            printBoard(board, boardDim);
        }
        
        // if comp has no available move
        else if (availableMoves(board, boardDim, playerColour))
            printf("%c player has no valid move.\n", compColour);
    }
    
    // decide winner
    char winnerColour = winner(board, boardDim, playerColour, compColour);
    if (winnerColour == 'B' || winnerColour == 'W')
        printf("%c player wins.\n", winnerColour);
    else
        printf("Draw!\n");

    return 0;
}


#endif // DO NOT DELETE THIS LINE
