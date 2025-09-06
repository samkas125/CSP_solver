#include "minesweeper_class.hpp"

/**
 * Legacy solve function for backward compatibility.
 * This function delegates to the new modular MinesweeperSolver class.
 * 
 * @param board Reference to the Minesweeper board to solve
 * @param x The iteration number (used for RREF skipping)
 */
void solve(MSBoard& board, int x);