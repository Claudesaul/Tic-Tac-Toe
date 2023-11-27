#include <stdio.h>

// Function to initialize the board
void initializeBoard(char board[3][3]) {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

// Function to display the current board
void displayBoard(char board[3][3]) {
    printf("Current board:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the selected move is valid
int isValidMove(char board[3][3], int move) {
    // Convert the move to board indices
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    // Check if the chosen cell is empty
    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return 0; // Invalid move
    } else {
        return 1; // Valid move
    }
}

// Function to check if the game is over
int isGameOver(char board[3][3]) {
    // Check rows, columns, and diagonals for a winner
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return 1; // Winner in rows
        }
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return 1; // Winner in columns
        }
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return 1; // Winner in top-left to bottom-right diagonal
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return 1; // Winner in top-right to bottom-left diagonal
    }

    // Check for a tie
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0; // Game is not over
            }
        }
    }

    return -1; // Game is a tie
}

int main() {
    char board[3][3];
    int move;
    char currentPlayer = 'X';
    int playerXScore = 0, playerOScore = 0;

    do {
        initializeBoard(board);
        displayBoard(board);

        while (1) {
            printf("Player %c's turn. Enter a number (1-9): ", currentPlayer);
            scanf("%d", &move);

            if (move < 1 || move > 9 || !isValidMove(board, move)) {
                printf("Invalid move, try again.\n");
                continue;
            }

            // Convert the move to board indices
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            // Make the move
            board[row][col] = currentPlayer;
            displayBoard(board);

            int result = isGameOver(board);
            if (result == 1) {
                printf("Player %c wins!\n", currentPlayer);
                if (currentPlayer == 'X') {
                    playerXScore++;
                } else {
                    playerOScore++;
                }
                break;
            } else if (result == -1) {
                printf("It's a tie!\n");
                break;
            }

            // Switch players
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        printf("Current Score - Player X: %d, Player O: %d\n", playerXScore, playerOScore);

        // Ask if they want to play again
        char playAgain;
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain); // Note the space before %c to consume the newline character

        if (playAgain != 'y' && playAgain != 'Y') {
            printf("Thanks for playing!\n");
            break;
        }

    } while (1);

    return 0;
}