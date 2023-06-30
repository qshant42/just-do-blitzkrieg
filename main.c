/*******************************
Name: Just do Blitzkrieg
Vesrion: 1.0.0
Author: Shant J. Sarkissian 
Language: C 
Date: 01 Jul 2023
*******************************/
    
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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
    if (from[0] >= 'A' && from[0] <= 'H' && from[1] >= '1' && from[1] <= '8' &&
        to[0] >= 'A' && to[0] <= 'H' && to[1] >= '1' && to[1] <= '8') {

        int fromRow = from[1] - '1';
        int fromCol = from[0] - 'A';
        int toRow = to[1] - '1';
        int toCol = to[0] - 'A';

        char piece = chessboard[fromRow][fromCol];

        switch (piece) {
            case 'P': // White Pawn
                if (fromCol == toCol && toRow == fromRow + 1 && chessboard[toRow][toCol] == ' ')
                    return 1;
                if (fromCol == toCol && fromRow == 1 && toRow == 3 && chessboard[2][toCol] == ' ' && chessboard[3][toCol] == ' ')
                    return 1;
                if (abs(toCol - fromCol) == 1 && toRow == fromRow + 1 && islower(chessboard[toRow][toCol]))
                    return 1;
                break;
            case 'p': // Black Pawn
                if (isupper(chessboard[toRow][toCol])) {
                    if (abs(toCol - fromCol) == 1 && toRow == fromRow - 1)
                        return 1;
                } else {
                    if (fromCol == toCol && toRow == fromRow - 1 && chessboard[toRow][toCol] == ' ')
                        return 1;
                    if (fromCol == toCol && fromRow == 6 && toRow == 4 && chessboard[5][toCol] == ' ' && chessboard[4][toCol] == ' ')
                        return 1;
                }
                break;    
            case 'R': // White Rook
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol))
                    return 1;
                break;
            case 'r': // Black Rook
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol))
                    return 1;
                break;
            case 'N': // White Knight
                if ((abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1) || (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 2))
                    return 1;
                break;
            case 'n': // Black Knight
                if ((abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1) || (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 2))
                    return 1;
                break;    
            case 'B': // White Bishop
                if (abs(toRow - fromRow) == abs(toCol - fromCol))
                    return 1;
                break;
            case 'b': // Black Bishop
                if (abs(toRow - fromRow) == abs(toCol - fromCol))
                    return 1;
                break;
            case 'Q': // White Queen
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol) ||
                    (abs(toRow - fromRow) == abs(toCol - fromCol)))
                    return 1;
                break;
            case 'q': // Black Queen
                if ((fromRow == toRow && fromCol != toCol) || (fromRow != toRow && fromCol == toCol) ||
                    (abs(toRow - fromRow) == abs(toCol - fromCol)))
                    return 1;
                break;
            case 'K': // White King
                if (abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1)
                    return 1;
                break;
            case 'k': // Black King
                if (abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1)
                    return 1;
                break;
        }
    }

    return 0; // Default: Invalid input or move not allowed for the piece
}

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

    printChessboard(chessboard);

    while (1) {
        printf("Player %c's turn:\n", currentPlayer);
        printf("Enter the position of the figure you want to move from: ");
        scanf(" %s", from);

        int fromRow = from[1] - '1';
        int fromCol = from[0] - 'A';
        if (chessboard[fromRow][fromCol] == ' ') {
            printf("Invalid move! There is no figure at the selected position.\n\n");
            continue;
        }

        printf("Enter the position you want to move to: ");
        scanf(" %s", to);

        if (!isValidInput(from, to, chessboard)) {
            printf("Invalid input! Please enter positions within the range (A1 to H8).\n\n");
            continue;
        }

        if ((currentPlayer == 'W' && chessboard[fromRow][fromCol] >= 'a' && chessboard[fromRow][fromCol] <= 'z') ||
            (currentPlayer == 'B' && chessboard[fromRow][fromCol] >= 'A' && chessboard[fromRow][fromCol] <= 'Z')) {
            printf("Invalid move! Please select your own figure.\n\n");
            continue;
        }

        moveFigure(chessboard, from, to, currentPlayer);

        printChessboard(chessboard);

        currentPlayer = (currentPlayer == 'W') ? 'B' : 'W';
    }

    return 0;
}


int isCheck(char chessboard[8][8], char player) {
    int kingRow = -1;
    int kingCol = -1;

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

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((player == 'w' && islower(chessboard[row][col])) || (player == 'b' && isupper(chessboard[row][col]))) {
                char piece = chessboard[row][col];
                char opponentKing = (player == 'w') ? 'k' : 'K';

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

bool isCheckmate(char chessboard[8][8], char player) {
    if (!isCheck(chessboard, player))
        return false; // The player is not in check, so not in checkmate

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((player == 'w' && isupper(chessboard[row][col])) || (player == 'b' && islower(chessboard[row][col]))) {
                for (int toRow = 0; toRow < 8; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        char from[2];
                        char to[2];

                        from[0] = col + 'A';
                        from[1] = '8' - row;
                        to[0] = toCol + 'A';
                        to[1] = '8' - toRow;

                        if (isValidInput(from, to, chessboard)) {
                            char piece = chessboard[row][col];
                            chessboard[row][col] = ' ';
                            chessboard[toRow][toCol] = piece;

                            if (!isCheck(chessboard, player)) {
                                chessboard[row][col] = piece;
                                chessboard[toRow][toCol] = ' ';
                                return false;
                            }

                            chessboard[row][col] = piece;
                            chessboard[toRow][toCol] = ' ';
                        }
                    }
                }
            }
        }
    }

    return true;
}
