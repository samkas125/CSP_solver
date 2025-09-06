#include "equation_builder.hpp"
#include <algorithm>

TwoWayDict EquationBuilder::identifyUnrevealedSquares(const std::vector<std::vector<int>>& state, 
                                                     int rows, int cols) {
    TwoWayDict unrevealed_indices;
    int index_counter = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (state[r][c] >= 0) { // Revealed square
                auto neighbors = getNeighbors(r, c, rows, cols);
                
                for (const auto& neighbor : neighbors) {
                    int nr = neighbor.first;
                    int nc = neighbor.second;
                    
                    if (state[nr][nc] == SolverConstants::UNREVEALED && 
                        !unrevealed_indices.contains_key(nr * cols + nc)) {
                        unrevealed_indices.insert(nr * cols + nc, index_counter);
                        index_counter++;
                    }
                }
            }
        }
    }
    return unrevealed_indices;
}

std::vector<std::vector<int>> EquationBuilder::createEquations(const std::vector<std::vector<int>>& state,
                                                              const TwoWayDict& unrevealed_indices,
                                                              int rows, int cols) {
    std::vector<std::vector<int>> equations;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (state[r][c] >= 0) { // Revealed square
                auto neighbors = getNeighbors(r, c, rows, cols);
                std::vector<int> neighbor_indices;
                int mine_count = state[r][c];

                // Count marked mines and collect unrevealed neighbor indices
                for (const auto& neighbor : neighbors) {
                    int nr = neighbor.first;
                    int nc = neighbor.second;
                    
                    if (state[nr][nc] == SolverConstants::MARKED_MINE) {
                        mine_count--;
                    } else if (unrevealed_indices.contains_key(nr * cols + nc)) {
                        neighbor_indices.push_back(unrevealed_indices.get_value(nr * cols + nc));
                    }
                }

                // Create equation if there are unrevealed neighbors
                if (!neighbor_indices.empty()) {
                    std::vector<int> equation(unrevealed_indices.size(), 0);
                    
                    // Set coefficients for unrevealed neighbors
                    for (int idx : neighbor_indices) {
                        equation[idx] = 1;
                    }
                    
                    equation.push_back(mine_count); // RHS of equation
                    equations.push_back(equation);
                }
            }
        }
    }
    return equations;
}

std::vector<std::pair<int, int>> EquationBuilder::getNeighbors(int r, int c, int rows, int cols) {
    std::vector<std::pair<int, int>> neighbors;
    
    for (const auto& direction : SolverConstants::NEIGHBOR_DIRECTIONS) {
        int nr = r + direction[0];
        int nc = c + direction[1];
        
        if (isValidPosition(nr, nc, rows, cols)) {
            neighbors.emplace_back(nr, nc);
        }
    }
    
    return neighbors;
}

bool EquationBuilder::isValidPosition(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}
