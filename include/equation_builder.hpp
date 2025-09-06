#ifndef EQUATION_BUILDER_HPP
#define EQUATION_BUILDER_HPP

#include <vector>
#include "two_way_dict.hpp"
#include "solver_constants.hpp"

/**
 * Helper class for building linear equations from Minesweeper board state.
 * This class encapsulates the logic for identifying unrevealed squares
 * and creating constraint equations.
 */
class EquationBuilder {
public:
    /**
     * Identify all unrevealed squares that are adjacent to revealed squares.
     * @param state The current board state
     * @param rows Number of rows in the board
     * @param cols Number of columns in the board
     * @return A TwoWayDict mapping board positions to equation indices
     */
    static TwoWayDict identifyUnrevealedSquares(const std::vector<std::vector<int>>& state, 
                                               int rows, int cols);

    /**
     * Create linear equations from the board state.
     * @param state The current board state
     * @param unrevealed_indices Mapping of unrevealed squares to equation indices
     * @param rows Number of rows in the board
     * @param cols Number of columns in the board
     * @return Vector of equations, where each equation is a vector of coefficients
     */
    static std::vector<std::vector<int>> createEquations(const std::vector<std::vector<int>>& state,
                                                         const TwoWayDict& unrevealed_indices,
                                                         int rows, int cols);

private:
    /**
     * Get all neighbors of a cell at position (r, c).
     * @param r Row index
     * @param c Column index
     * @param rows Total number of rows
     * @param cols Total number of columns
     * @return Vector of (row, col) pairs representing valid neighbors
     */
    static std::vector<std::pair<int, int>> getNeighbors(int r, int c, int rows, int cols);

    /**
     * Check if a position is within board bounds.
     * @param r Row index
     * @param c Column index
     * @param rows Total number of rows
     * @param cols Total number of columns
     * @return True if position is valid, false otherwise
     */
    static bool isValidPosition(int r, int c, int rows, int cols);
};

#endif // EQUATION_BUILDER_HPP
