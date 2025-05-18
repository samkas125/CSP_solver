#include <iostream>
#include <vector>
#include <list>
#define ARMA_DONT_USE_STD_MUTEX
#include <armadillo>
#include "minesweeper_class.hpp"   
#include "arma_helper.hpp"

class TwoWayDict {
private:
    std::map<int, int> forward_map;
    std::map<int, int> reverse_map;

public:

    void insert(int key, int value) {
        if (forward_map.find(key) != forward_map.end()) {
            int old_value = forward_map[key];
            forward_map.erase(key);
            reverse_map.erase(old_value);
        }
        if (reverse_map.find(value) != reverse_map.end()) {
            int old_key = reverse_map[value];
            reverse_map.erase(value);
            forward_map.erase(old_key);
        }
        
        forward_map[key] = value;
        reverse_map[value] = key;
    }

    void erase(int key) {
        if (forward_map.find(key) != forward_map.end()) {
            int value = forward_map[key];
            forward_map.erase(key);
            reverse_map.erase(value);
        }
    }

    int size() const {
        return forward_map.size();
    }

    bool contains_key(int key) const {
        return forward_map.find(key) != forward_map.end();
    }

    int get_value(int key) const {
        return forward_map.at(key);
    }

    int get_key(int value) const {
        return reverse_map.at(value);
    }

    std::vector<int> get_keys() const {
        std::vector<int> keys;
        for (const auto& pair : forward_map) {
            keys.push_back(pair.first);
        }
        return keys;
    }
};

// Helper function to identify unrevealed squares
TwoWayDict identifyUnrevealedSquares(const std::vector<std::vector<int>>& state, int rows, int cols) {
    TwoWayDict unrevealed_indices;
    int index_counter = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (state[r][c] >= 0) { // Revealed square
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr != 0 || dc != 0) { // Neighboring cells
                            int nr = r + dr;
                            int nc = c + dc;
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                                if (state[nr][nc] == -1 && !unrevealed_indices.contains_key(nr * cols + nc)) {
                                    unrevealed_indices.insert(nr * cols + nc, index_counter);
                                    index_counter++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return unrevealed_indices;
}

// Helper function to create equations
std::vector<std::vector<int>> createEquations(const std::vector<std::vector<int>>& state, const TwoWayDict& unrevealed_indices, int rows, int cols) {
    std::vector<std::vector<int>> equations;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (state[r][c] >= 0) { // Revealed square
                std::vector<int> neighbors;
                int mine_count = state[r][c];

                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr != 0 || dc != 0) { // Neighboring cells
                            int nr = r + dr;
                            int nc = c + dc;
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                                if (state[nr][nc] == -2) // Marked as mine
                                    mine_count--;
                                if (unrevealed_indices.contains_key(nr * cols + nc)) 
                                    neighbors.push_back(unrevealed_indices.get_value(nr * cols + nc));
                            }
                        }
                    }
                }

                if (!neighbors.empty()) { // Create equation
                    std::vector<int> equation(unrevealed_indices.size(), 0);
                    for (int idx : neighbors)
                        equation[idx] = 1;

                    equation.push_back(mine_count); // RHS of equation
                    equations.push_back(equation);
                }
            }
        }
    }
    return equations;
}

// Helper function to process RREF
void processRREF(const std::vector<std::vector<int>>& rrefVector, const TwoWayDict& unrevealed_indices, MSBoard& board, int cols) {
    for (const auto& row : rrefVector) {
        int min = 0;
        int max = 0;
        for (int i = 0; i < row.size() - 1; i++) {
            if (row[i] > 0) max += row[i];
            if (row[i] < 0) min += row[i];
        }
        if (row[row.size() - 1] == min) { // Process min case
            for (int i = 0; i < row.size() - 1; i++) {
                if (row[i] < 0) {
                    int idx = unrevealed_indices.get_key(i);
                    int r = idx / cols;
                    int c = idx % cols;
                    board.markMine(r, c);
                }
                if (row[i] > 0) {
                    int idx = unrevealed_indices.get_key(i);
                    int r = idx / cols;
                    int c = idx % cols;
                    board.open(r, c);
                }
            }
        }
        if (row[row.size() - 1] == max) { // Process max case
            for (int i = 0; i < row.size() - 1; i++) {
                if (row[i] > 0) {
                    int idx = unrevealed_indices.get_key(i);
                    int r = idx / cols;
                    int c = idx % cols;
                    board.markMine(r, c);
                }
                if (row[i] < 0) {
                    int idx = unrevealed_indices.get_key(i);
                    int r = idx / cols;
                    int c = idx % cols;
                    board.open(r, c);
                }
            }
        }
    }
}

void solve(MSBoard& board, int x) {
    std::vector<std::vector<int>> state = board.revealedBoard;
    int rows = state.size();
    int cols = state[0].size();

    // Identify unrevealed squares
    TwoWayDict unrevealed_indices = identifyUnrevealedSquares(state, rows, cols);

    // Create equations
    std::vector<std::vector<int>> equations = createEquations(state, unrevealed_indices, rows, cols);

    if (equations.empty() || equations[0].empty()) return; // No equations

    // Compute RREF
    arma::mat A = convert_to_arma_mat(equations);
    arma::mat RREF = compute_rref(A);
    std::vector<std::vector<int>> rrefVector = convert_to_vector(RREF);

    if (x % 3 == 2) rrefVector = equations; // Process without RREF 1/3rd times - RREF misses solutions sometimes

    // Process RREF
    processRREF(rrefVector, unrevealed_indices, board, cols);
}

// int main() {
//     MSBoard board = MSBoard(14, 18, 40);
//     board.open(3, 3);
//     for (int i = 0; i < 100; i++) {
//         solve(board, i);
//     }
//     for (const auto& row : board.board) {
//         for (int cell : row) {
//             if (cell == -1) printf("+");
//             else printf("%d", cell);
//             printf("  ");
//         }
//         std::cout << std::endl;
//     }
//     printf("\n\n\n");

//     // Print result matrix
//     for (const auto& row : board.revealedBoard) {
//         for (int cell : row) {
//             if (cell == -1) printf("*");
//             else if (cell == -2) printf("+");
//             else printf("%d", cell);
//             printf("  ");
//         }
//         std::cout << std::endl;
//     }

//     return 0;
//     // board.board[0][0] = 0;
//     // board.board[0][1] = 0;
//     // board.board[0][2] = 1;
//     // board.board[0][3] = 1;
//     // board.board[1][0] = 0;
//     // board.board[1][1] = 0;
//     // board.board[1][2] = 2;
//     // board.board[1][3] = -1;
//     // board.board[2][0] = 1;
//     // board.board[2][1] = 1;
//     // board.board[2][2] = 4;
//     // board.board[2][3] = -1;
//     // board.board[3][0] = 1;
//     // board.board[3][1] = -1;
//     // board.board[3][2] = 3;
//     // board.board[3][3] = -1;
//     // board.started = true;
// }
