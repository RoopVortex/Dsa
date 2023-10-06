#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 4
#define COLUMNS 5
#define RED 'R'
#define BLUE 'B'
#define EMPTY ' '

typedef char bt[ROWS][COLUMNS];
typedef char pt;

// Initialize the board with empty spaces.
void initializeBoard(bt board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Display the current state of the board.
void printBoard(bt board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("  1   2   3   4   5\n");
}

// Drop a piece in the specified column.
bool dropPiece(bt board, int column, pt player) {
    if (column < 1 || column > COLUMNS) {
        printf("Invalid column. Please choose a column between 1 and 5.\n");
        return false;
    }

    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][column - 1] == EMPTY) {
            board[i][column - 1] = player;
            return true;
        }
    }

    printf("Column is full. Please choose another column.\n");
    return false;
}

// Check if a player has won.
bool hasWon(bt board, pt player) {
    // Check for horizontal win
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return true;
            }
        }
    }

    // Check for vertical win
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return true;
            }
        }
    }

    // Check for diagonal win (bottom-left to top-right)
    for (int row = 3; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return true;
            }
        }
    }

    // Check for diagonal win (top-left to bottom-right)
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return true;
            }
        }
    }

    return false;
}

    // Implement the win-checking logic (horizontal, vertical, and diagonal)
    // Return true if the player has won, false otherwise.
    // This is where you should add the win-checking logi

// Check if the board is full.
bool isFull(bt board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Computer AI: Find the best move for the computer player (for a basic AI).
int bestMove(bt board, pt player) {
    // Implement a simple AI strategy to find the best move.
    for (int col = 0; col < COLUMNS; col++) {
        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] == EMPTY) {
                return col + 1; // Return the column to play the piece.
            }
        }
    }
    return -1; // No valid move found.
}

// Main game logic
int main() {
    bt board;
    initializeBoard(board);

    pt humanPlayer;
    printf("Enter 'R' for red player or 'B' for blue player: ");
    scanf(" %c", &humanPlayer);

    if (humanPlayer != RED && humanPlayer != BLUE) {
        printf("Invalid player choice. Please choose 'R' or 'B'.\n");
        return 1;
    }

    pt computerPlayer = (humanPlayer == RED) ? BLUE : RED;

    int moves = 0;
    printf("Welcome to Connect Four!\n");
    printBoard(board);

    while (true) {
        if (moves % 2 == 0) {
            // Human player's turn
            int column;
            printf("Player %c's turn. Choose a column (1-5): ", humanPlayer);
            scanf("%d", &column);

            if (dropPiece(board, column, humanPlayer)) {
                moves++;
                printBoard(board);

                if (hasWon(board, humanPlayer)) {
                    printf("Player %c wins! Congratulations!\n", humanPlayer);
                    break;
                } else if (isFull(board)) {
                    printf("It's a draw!\n");
                    break;
                }
            }
        } else {
            // Computer player's turn
            printf("Computer (Player %c)'s turn...\n", computerPlayer);
            int column = bestMove(board, computerPlayer);

            if (column != -1) {
                dropPiece(board, column, computerPlayer);
                moves++;
                printBoard(board);

                if (hasWon(board, computerPlayer)) {
                    printf("Player %c wins! Congratulations!\n", computerPlayer);
                    break;
                } else if (isFull(board)) {
                    printf("It's a draw!\n");
                    break;
                }
            }
        }
    }

    return 0;
}