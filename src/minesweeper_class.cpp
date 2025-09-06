#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "minesweeper_class.hpp"
#include <SFML/Graphics.hpp>

MSBoard::MSBoard(int numRows, int numCols, int numMines) {
    rows = numRows;
    cols = numCols;
    mines = numMines;
    board = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    revealedBoard = std::vector<std::vector<int>>(rows, std::vector<int>(cols, -1)); 
    unsigned int x = std::time(0);
    // x = 1747481856;
    std::srand(x); // Seed for random number generation
    printf("Seed: %d\n", x);
}

void MSBoard::open(int row, int col) {
    revealedBoard[row][col] = board[row][col];
    if (!started) {
        MSBoard::placeMines(row, col);
        started = true;
    }
    if (board[row][col] == -1) {
        printf("Game Over!");
        exit(0);
        // Game over
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                revealedBoard[r][c] = board[r][c];
            }
        }
    }
}

void MSBoard::markMine(int row, int col) {
    if (revealedBoard[row][col] == -1) {
        revealedBoard[row][col] = -2;
    }
}

void MSBoard::placeMines(int row, int col) {
    int placedMines = 0;  
    while (placedMines < mines) {
        int r = std::rand() % rows;
        int c = std::rand() % cols;

        // Check if the position is valid for placing a mine
        if (board[r][c] == 0 && !isAdjacent(r, c, row, col) && !(r == row && c == col)) {
            board[r][c] = -1; // Place a mine
            placedMines++;
        }
    }
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (board[i][j] != -1) {
                int count = 0;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        int nr = i + dr;
                        int nc = j + dc;
                        if (nr >= 0 && nr < this->rows && nc >= 0 && nc < this->cols) {
                            if (board[nr][nc] == -1) {
                                count++;
                            }
                        }
                    }
                }
                board[i][j] = count;
            }
        }
    }
}

bool MSBoard::isAdjacent(int r, int c, int initialRow, int initialCol) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int nr = initialRow + dr;
            int nc = initialCol + dc;
            if (nr == r && nc == c) {
                return true;
            }
        }
    }
    return false;
}

bool MSBoard::isSolved() {
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            if (revealedBoard[r][c] == -1) return false;
        }
    }
    return true;
}

// int main() {
//     MSBoard board(10, 10, 20);
//     board.open(5, 5);
//     board.open(5, 6);
//     board.open(5, 4);
//     board.open(6, 5);
//     board.open(4, 5);
//     board.open(4, 4);
//     board.open(6, 4);
//     board.open(4, 6);
//     board.open(6, 6);

//     // Print the board for debugging
//     for (const auto& row : board.revealedBoard) {
//         for (int cell : row) {
//             if (cell == -1) printf("*");
//             else printf("%d", cell);
//             printf(" ");
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }