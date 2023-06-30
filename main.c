#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


// Function to print the chessboard
void printChessboard(char chessboard[8][8]) {
    printf("\n  +---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("| %c ", chessboard[i][j]);
        }
        printf("|\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    A   B   C   D   E   F   G   H\n\n");
}

int isValidInput(char from[2], char to[2], char chessboard[8][8]) {
    // Check if the input coordinates are within the chessboard range
    if (from[0] >= 'A' && from[0] <= 'H' && from[1] >= '1' && from[1] <= '8' &&
        to[0] >= 'A' && to[0] <= 'H' && to[1] >= '1' && to[1] <= '8') {

        int fromRow = from[1] - '1';
        int fromCol = from[0] - 'A';
        int toRow = to[1] - '1';
        int toCol = to[0] - 'A';

        // Get the piece at the from position
        char piece = chessboard[fromRow][fromCol];

        // Check for valid moves based on the piece
        switch (piece) {
            case 'P': // White Pawn
                // Check if the move is one step forward
                if (fromCol == toCol && toRow == fromRow + 1 && chessboard[toRow][toCol] == ' ')
                    return 1;
                // Check if the move is two steps forward from the starting position
                if (fromCol == toCol && fromRow == 1 && toRow == 3 && chessboard[2][toCol] == ' ' && chessboard[3][toCol] == ' ')
                    return 1;
                // Check if the move is a diagonal capture
                if (abs(toCol - fromCol) == 1 && toRow == fromRow + 1 && islower(chessboard[toRow][toCol]))
                    return 1;
                break;
            case 'p': // Black Pawn
                if (isupper(chessboard[toRow][toCol])) {
                    // Check if the move is a diagonal capture for black pawn
                    if (abs(toCol - fromCol) == 1 && toRow == fromRow - 1)
                        return 1;
                } else {
                    // Check if the move is one step forward for black pawn
                    if (fromCol == toCol && toRow == fromRow - 1 && chessboard[toRow][toCol] == ' ')
                        return 1;
                    // Check if the move is two steps forward from the starting position for black pawn
                    if (fromCol == toCol && fromRow == 6 && toRow == 4 && chessboard[5][toCol] == ' ' && chessboard[4][toCol] == ' ')
                        return 1;
                }
                break;    
            case 'R': // White Rook
                // Check if the move is along the same row or column
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol))
                    return 1;
                break;
            case 'r': // Black Rook
                // Check if the move is along the same row or column
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol))
                    return 1;
                break;
            case 'N': // White Knight
                // Check if the move is an L-shape (2 steps in one direction and 1 step in a perpendicular direction)
                if ((abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1) || (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 2))
                    return 1;
                break;
            case 'n': // Black Knight
                // Check if the move is an L-shape (2 steps in one direction and 1 step in a perpendicular direction)
                if ((abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1) || (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 2))
                    return 1;
                break;    
            case 'B': // White Bishop
                // Check if the move is along a diagonal
                if (abs(toRow - fromRow) == abs(toCol - fromCol))
                    return 1;
                break;
            case 'b': // Black Bishop
                // Check if the move is along a diagonal
                if (abs(toRow - fromRow) == abs(toCol - fromCol))
                    return 1;
                break;
            case 'Q': // White Queen
                // Check if the move is along the same row, column, or diagonal
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol) ||
                    (abs(toRow - fromRow) == abs(toCol - fromCol)))
                    return 1;
                break;
            case 'q': // Black Queen
                // Check if the move is along the same row, column, or diagonal
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol) ||
                    (abs(toRow - fromRow) == abs(toCol - fromCol)))
                    return 1;
                break;
            case 'K': // White King
                // Check if the move is one step in any direction
                if (abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1)
                    return 1;
                break;
            case 'k': // Black King
                // Check if the move is one step in any direction
                if (abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1)
                    return 1;
                break;
        }
    }

    return 0; // Default: Invalid input or move not allowed for the piece
}

// Function to move a figure on the chessboard
void moveFigure(char chessboard[8][8], char from[2], char to[2], char currentPlayer) {
    int fromRow = from[1] - '1';
    int fromCol = from[0] - 'A';
    int toRow = to[1] - '1';
    int toCol = to[0] - 'A';

    chessboard[toRow][toCol] = chessboard[fromRow][fromCol];
    chessboard[fromRow][fromCol] = ' ';

    // Print the move
    printf("%c moved from %s to %s\n", currentPlayer, from, to);
}

int main() {
    char chessboard[8][8] = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };

    char from[2];
    char to[2];
    char currentPlayer = 'W'; // Player W (White) starts

    // Print the initial chessboard
    printChessboard(chessboard);

    while (1) {
        // Get user input
        printf("Player %c's turn:\n", currentPlayer);
        printf("Enter the position of the figure you want to move from: ");
        scanf(" %s", from);

        // Validate the selected position contains a figure
        int fromRow = from[1] - '1';
        int fromCol = from[0] - 'A';
        if (chessboard[fromRow][fromCol] == ' ') {
            printf("Invalid move! There is no figure at the selected position.\n\n");
            continue;
        }

        printf("Enter the position you want to move to: ");
        scanf(" %s", to);

        // Validate the user input
        if (!isValidInput(from, to, chessboard)) {
            printf("Invalid input! Please enter positions within the range (A1 to H8).\n\n");
            continue;
        }

        // Check if the figure belongs to the current player
        if ((currentPlayer == 'W' && chessboard[fromRow][fromCol] >= 'a' && chessboard[fromRow][fromCol] <= 'z') ||
            (currentPlayer == 'B' && chessboard[fromRow][fromCol] >= 'A' && chessboard[fromRow][fromCol] <= 'Z')) {
            printf("Invalid move! Please select your own figure.\n\n");
            continue;
        }

        // Move the figure on the chessboard
        moveFigure(chessboard, from, to, currentPlayer);

        // Print the updated chessboard
        printChessboard(chessboard);

        // Switch the player
        currentPlayer = (currentPlayer == 'W') ? 'B' : 'W';
    }

    return 0;
}


int isCheck(char chessboard[8][8], char player) {
    int kingRow = -1;
    int kingCol = -1;

    // Find the position of the king of the specified player
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((player == 'w' && chessboard[row][col] == 'K') || (player == 'b' && chessboard[row][col] == 'k')) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1 && kingCol != -1)
            break;
    }

    // Check if any opponent's piece can attack the king
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((player == 'w' && islower(chessboard[row][col])) || (player == 'b' && isupper(chessboard[row][col]))) {
                char piece = chessboard[row][col];
                char opponentKing = (player == 'w') ? 'k' : 'K';

                // Check if the opponent's piece can attack the king
                switch (piece) {
                    case 'P': // White Pawn
                        if (player == 'b') {
                            if (row + 1 < 8 && col - 1 >= 0 && chessboard[row + 1][col - 1] == opponentKing)
                                return 1;
                            if (row + 1 < 8 && col + 1 < 8 && chessboard[row + 1][col + 1] == opponentKing)
                                return 1;
                        }
                        break;
                    case 'p': // Black Pawn
                        if (player == 'w') {
                            if (row - 1 >= 0 && col - 1 >= 0 && chessboard[row - 1][col - 1] == opponentKing)
                                return 1;
                            if (row - 1 >= 0 && col + 1 < 8 && chessboard[row - 1][col + 1] == opponentKing)
                                return 1;
                        }
                        break;
                    case 'R': // White Rook
                        if (row == kingRow || col == kingCol) {
                            int step = (row == kingRow) ? ((col < kingCol) ? 1 : -1) : ((row < kingRow) ? 1 : -1);
                            int i = (row == kingRow) ? col + step : row + step;
                            while (i != kingCol && i >= 0 && i < 8) {
                                if (chessboard[(row == kingRow) ? row : i][(row == kingRow) ? i : col] == opponentKing)
                                    return 1;
                                i += step;
                            }
                        }
                        break;
                    case 'r': // Black Rook
                        if (row == kingRow || col == kingCol) {
                            int step = (row == kingRow) ? ((col < kingCol) ? 1 : -1) : ((row < kingRow) ? 1 : -1);
                            int i = (row == kingRow) ? col + step : row + step;
                            while (i != kingCol && i >= 0 && i < 8) {
                                if (chessboard[(row == kingRow) ? row : i][(row == kingRow) ? i : col] == opponentKing)
                                    return 1;
                                i += step;
                            }
                        }
                        break;
                    case 'N': // White Knight
                        if (abs(row - kingRow) == 2 && abs(col - kingCol) == 1)
                            return 1;
                        if (abs(row - kingRow) == 1 && abs(col - kingCol) == 2)
                            return 1;
                        break;
                    case 'n': // Black Knight
                        if (abs(row - kingRow) == 2 && abs(col - kingCol) == 1)
                            return 1;
                        if (abs(row - kingRow) == 1 && abs(col - kingCol) == 2)
                            return 1;
                        break;
                    case 'B': // White Bishop
                        if (abs(row - kingRow) == abs(col - kingCol)) {
                            int rowStep = (row < kingRow) ? 1 : -1;
                            int colStep = (col < kingCol) ? 1 : -1;
                            int i = row + rowStep;
                            int j = col + colStep;
                            while (i != kingRow && j != kingCol && i >= 0 && i < 8 && j >= 0 && j < 8) {
                                if (chessboard[i][j] == opponentKing)
                                    return 1;
                                i += rowStep;
                                j += colStep;
                            }
                        }
                        break;
                    case 'b': // Black Bishop
                        if (abs(row - kingRow) == abs(col - kingCol)) {
                            int rowStep = (row < kingRow) ? 1 : -1;
                            int colStep = (col < kingCol) ? 1 : -1;
                            int i = row + rowStep;
                            int j = col + colStep;
                            while (i != kingRow && j != kingCol && i >= 0 && i < 8 && j >= 0 && j < 8) {
                                if (chessboard[i][j] == opponentKing)
                                    return 1;
                                i += rowStep;
                                j += colStep;
                            }
                        }
                        break;
                    case 'Q': // White Queen
                        if (row == kingRow || col == kingCol || abs(row - kingRow) == abs(col - kingCol)) {
                            if (row == kingRow || col == kingCol) {
                                int step = (row == kingRow) ? ((col < kingCol) ? 1 : -1) : ((row < kingRow) ? 1 : -1);
                                int i = (row == kingRow) ? col + step : row + step;
                                while (i != kingCol && i >= 0 && i < 8) {
                                    if (chessboard[(row == kingRow) ? row : i][(row == kingRow) ? i : col] == opponentKing)
                                        return 1;
                                    i += step;
                                }
                            } else {
                                int rowStep = (row < kingRow) ? 1 : -1;
                                int colStep = (col < kingCol) ? 1 : -1;
                                int i = row + rowStep;
                                int j = col + colStep;
                                while (i != kingRow && j != kingCol && i >= 0 && i < 8 && j >= 0 && j < 8) {
                                    if (chessboard[i][j] == opponentKing)
                                        return 1;
                                    i += rowStep;
                                    j += colStep;
                                }
                            }
                        }
                        break;
                    case 'q': // Black Queen
                        if (row == kingRow || col == kingCol || abs(row - kingRow) == abs(col - kingCol)) {
                            if (row == kingRow || col == kingCol) {
                                int step = (row == kingRow) ? ((col < kingCol) ? 1 : -1) : ((row < kingRow) ? 1 : -1);
                                int i = (row == kingRow) ? col + step : row + step;
                                while (i != kingCol && i >= 0 && i < 8) {
                                    if (chessboard[(row == kingRow) ? row : i][(row == kingRow) ? i : col] == opponentKing)
                                        return 1;
                                    i += step;
                                }
                            } else {
                                int rowStep = (row < kingRow) ? 1 : -1;
                                int colStep = (col < kingCol) ? 1 : -1;
                                int i = row + rowStep;
                                int j = col + colStep;
                                while (i != kingRow && j != kingCol && i >= 0 && i < 8 && j >= 0 && j < 8) {
                                    if (chessboard[i][j] == opponentKing)
                                        return 1;
                                    i += rowStep;
                                    j += colStep;
                                }
                            }
                        }
                        break;
                    case 'K': // White King
                        if (abs(row - kingRow) <= 1 && abs(col - kingCol) <= 1)
                            return 1;
                        break;
                    case 'k': // Black King
                        if (abs(row - kingRow) <= 1 && abs(col - kingCol) <= 1)
                            return 1;
                        break;
                }
            }
        }
    }

    return 0; // Default: The opponent's king is not under attack
}
// Function to check if a player is in checkmate
bool isCheckmate(char chessboard[8][8], char player) {
    if (!isCheck(chessboard, player))
        return false; // The player is not in check, so not in checkmate

    // Iterate through all squares on the chessboard to find the player's pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((player == 'w' && isupper(chessboard[row][col])) || (player == 'b' && islower(chessboard[row][col]))) {
                // Check all possible moves for this piece
                for (int toRow = 0; toRow < 8; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        char from[2];
                        char to[2];

                        // Convert indices to positions
                        from[0] = col + 'A';
                        from[1] = '8' - row;
                        to[0] = toCol + 'A';
                        to[1] = '8' - toRow;

                        // Validate user input
                        if (isValidInput(from, to, chessboard)) {
                            // Simulate the move
                            char piece = chessboard[row][col];
                            chessboard[row][col] = ' ';
                            chessboard[toRow][toCol] = piece;

                            // Check if the move removes the check
                            if (!isCheck(chessboard, player)) {
                                // Undo the move
                                chessboard[row][col] = piece;
                                chessboard[toRow][toCol] = ' ';
                                return false;
                            }

                            // Undo the move
                            chessboard[row][col] = piece;
                            chessboard[toRow][toCol] = ' ';
                        }
                    }
                }
            }
        }
    }

    // If no legal move is found for any piece, the player is in checkmate
    return true;
}
