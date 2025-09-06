#ifndef RREF_PROCESSOR_HPP
#define RREF_PROCESSOR_HPP

#include <vector>
#include "two_way_dict.hpp"
#include "solver_constants.hpp"

// Forward declarations
class MSBoard;

/**
 * Helper class for processing Row-Reduced Echelon Form (RREF) matrices
 * to determine mine locations and safe cells in Minesweeper.
 */
class RREFProcessor {
public:
    /**
     * Process RREF matrix to determine mine locations and safe cells.
     * @param rrefVector The RREF matrix as a vector of vectors
     * @param unrevealed_indices Mapping of unrevealed squares to equation indices
     * @param board Reference to the Minesweeper board
     * @param cols Number of columns in the board
     */
    static void processRREF(const std::vector<std::vector<int>>& rrefVector,
                           const TwoWayDict& unrevealed_indices,
                           MSBoard& board,
                           int cols);

private:
    /**
     * Process a single equation row to determine mine locations and safe cells.
     * @param equation The equation row (coefficients + RHS)
     * @param unrevealed_indices Mapping of unrevealed squares to equation indices
     * @param board Reference to the Minesweeper board
     * @param cols Number of columns in the board
     */
    static void processEquation(const std::vector<int>& equation,
                               const TwoWayDict& unrevealed_indices,
                               MSBoard& board,
                               int cols);

    /**
     * Calculate the minimum possible value for the equation.
     * @param equation The equation coefficients (excluding RHS)
     * @return The minimum possible value
     */
    static int calculateMinValue(const std::vector<int>& equation);

    /**
     * Calculate the maximum possible value for the equation.
     * @param equation The equation coefficients (excluding RHS)
     * @return The maximum possible value
     */
    static int calculateMaxValue(const std::vector<int>& equation);

    /**
     * Convert a 1D index to 2D board coordinates.
     * @param index The 1D index
     * @param cols Number of columns in the board
     * @return Pair of (row, col) coordinates
     */
    static std::pair<int, int> indexToCoordinates(int index, int cols);

    /**
     * Mark a cell as a mine on the board.
     * @param board Reference to the Minesweeper board
     * @param r Row index
     * @param c Column index
     */
    static void markMine(MSBoard& board, int r, int c);

    /**
     * Open a cell on the board.
     * @param board Reference to the Minesweeper board
     * @param r Row index
     * @param c Column index
     */
    static void openCell(MSBoard& board, int r, int c);
};

#endif // RREF_PROCESSOR_HPP
