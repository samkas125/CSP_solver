#include "minesweeper_solver.hpp"
#include "minesweeper_class.hpp"
#include "../include/equation_builder.hpp"
#include "../include/rref_processor.hpp"
#include "../include/arma_helper.hpp"
#include <stdexcept>

bool MinesweeperSolver::solve(MSBoard& board, int iteration) {
    // Validate board state
    if (!validateBoard(board)) {
        return false;
    }

    // Store initial state for comparison
    std::vector<std::vector<int>> initial_state = board.revealedBoard;
    int rows = initial_state.size();
    int cols = initial_state[0].size();

    try {
        // Identify unrevealed squares
        TwoWayDict unrevealed_indices = EquationBuilder::identifyUnrevealedSquares(initial_state, rows, cols);
        
        if (unrevealed_indices.size() == 0) {
            return false; // No unrevealed squares to process
        }

        // Create equations
        std::vector<std::vector<int>> equations = EquationBuilder::createEquations(initial_state, unrevealed_indices, rows, cols);
        
        if (equations.empty() || equations[0].empty()) {
            return false; // No equations to solve
        }

        // Process equations
        if (shouldSkipRREF(iteration)) {
            // Process without RREF (original equations)
            RREFProcessor::processRREF(equations, unrevealed_indices, board, cols);
        } else {
            // Compute RREF and process
            arma::mat A = convert_to_arma_mat(equations);
            arma::mat RREF = compute_rref(A);
            std::vector<std::vector<int>> rrefVector = convert_to_vector(RREF);
            
            RREFProcessor::processRREF(rrefVector, unrevealed_indices, board, cols);
        }

        // Check if any progress was made
        return hasBoardChanged(initial_state, board.revealedBoard);

    } catch (const std::exception& e) {
        // Log error in a real implementation
        return false;
    }
}

bool MinesweeperSolver::validateBoard(const MSBoard& board) {
    if (board.revealedBoard.empty()) {
        return false;
    }
    
    int rows = board.revealedBoard.size();
    int cols = board.revealedBoard[0].size();
    
    if (rows <= 0 || cols <= 0) {
        return false;
    }
    
    // Check that all rows have the same number of columns
    for (const auto& row : board.revealedBoard) {
        if (row.size() != static_cast<size_t>(cols)) {
            return false;
        }
    }
    
    return true;
}

bool MinesweeperSolver::hasBoardChanged(const std::vector<std::vector<int>>& old_state,
                                       const std::vector<std::vector<int>>& new_state) {
    if (old_state.size() != new_state.size()) {
        return true;
    }
    
    for (size_t i = 0; i < old_state.size(); ++i) {
        if (old_state[i].size() != new_state[i].size()) {
            return true;
        }
        
        for (size_t j = 0; j < old_state[i].size(); ++j) {
            if (old_state[i][j] != new_state[i][j]) {
                return true;
            }
        }
    }
    
    return false;
}

bool MinesweeperSolver::shouldSkipRREF(int iteration) {
    return (iteration % SolverConstants::RREF_SKIP_FREQUENCY) == SolverConstants::RREF_SKIP_CONDITION;
}
