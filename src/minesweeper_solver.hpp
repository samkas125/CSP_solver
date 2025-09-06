#ifndef MINESWEEPER_SOLVER_HPP
#define MINESWEEPER_SOLVER_HPP

#include "../include/solver_constants.hpp"
#include <vector>

// Forward declarations
class MSBoard;

/**
 * Main solver class for Minesweeper using linear algebra.
 * This class orchestrates the solving process by building equations,
 * computing RREF, and processing the results.
 */
class MinesweeperSolver {
public:
    /**
     * Solve the Minesweeper board using linear algebra.
     * @param board Reference to the Minesweeper board to solve
     * @param iteration The current iteration number (used for RREF skipping)
     * @return True if any progress was made, false otherwise
     */
    static bool solve(MSBoard& board, int iteration = 0);

private:
    /**
     * Validate the board state before attempting to solve.
     * @param board Reference to the Minesweeper board
     * @return True if the board is valid for solving, false otherwise
     */
    static bool validateBoard(const MSBoard& board);

    /**
     * Check if the board state has changed after processing.
     * @param old_state The previous board state
     * @param new_state The current board state
     * @return True if the board state has changed, false otherwise
     */
    static bool hasBoardChanged(const std::vector<std::vector<int>>& old_state,
                               const std::vector<std::vector<int>>& new_state);

    /**
     * Determine whether to skip RREF computation for this iteration.
     * @param iteration The current iteration number
     * @return True if RREF should be skipped, false otherwise
     */
    static bool shouldSkipRREF(int iteration);
};

#endif // MINESWEEPER_SOLVER_HPP
