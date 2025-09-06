#include "rref_processor.hpp"
#include "../src/minesweeper_class.hpp"
#include <algorithm>

void RREFProcessor::processRREF(const std::vector<std::vector<int>>& rrefVector,
                               const TwoWayDict& unrevealed_indices,
                               MSBoard& board,
                               int cols) {
    for (const auto& equation : rrefVector) {
        if (equation.size() < 2) continue; // Skip invalid equations
        
        processEquation(equation, unrevealed_indices, board, cols);
    }
}

void RREFProcessor::processEquation(const std::vector<int>& equation,
                                   const TwoWayDict& unrevealed_indices,
                                   MSBoard& board,
                                   int cols) {
    if (equation.empty()) return;
    
    // Separate coefficients from RHS
    std::vector<int> coefficients(equation.begin(), equation.end() - 1);
    int rhs = equation.back();
    
    int min_val = calculateMinValue(coefficients);
    int max_val = calculateMaxValue(coefficients);
    
    // Process minimum case: all negative coefficients must be mines, all positive must be safe
    if (rhs == min_val) {
        for (size_t i = 0; i < coefficients.size(); ++i) {
            if (coefficients[i] < 0) {
                auto coords = indexToCoordinates(unrevealed_indices.get_key(i), cols);
                markMine(board, coords.first, coords.second);
            } else if (coefficients[i] > 0) {
                auto coords = indexToCoordinates(unrevealed_indices.get_key(i), cols);
                openCell(board, coords.first, coords.second);
            }
        }
    }
    
    // Process maximum case: all positive coefficients must be mines, all negative must be safe
    if (rhs == max_val) {
        for (size_t i = 0; i < coefficients.size(); ++i) {
            if (coefficients[i] > 0) {
                auto coords = indexToCoordinates(unrevealed_indices.get_key(i), cols);
                markMine(board, coords.first, coords.second);
            } else if (coefficients[i] < 0) {
                auto coords = indexToCoordinates(unrevealed_indices.get_key(i), cols);
                openCell(board, coords.first, coords.second);
            }
        }
    }
}

int RREFProcessor::calculateMinValue(const std::vector<int>& equation) {
    int min_val = 0;
    for (int coeff : equation) {
        if (coeff < 0) min_val += coeff;
    }
    return min_val;
}

int RREFProcessor::calculateMaxValue(const std::vector<int>& equation) {
    int max_val = 0;
    for (int coeff : equation) {
        if (coeff > 0) max_val += coeff;
    }
    return max_val;
}

std::pair<int, int> RREFProcessor::indexToCoordinates(int index, int cols) {
    return std::make_pair(index / cols, index % cols);
}

void RREFProcessor::markMine(MSBoard& board, int r, int c) {
    board.markMine(r, c);
}

void RREFProcessor::openCell(MSBoard& board, int r, int c) {
    board.open(r, c);
}
