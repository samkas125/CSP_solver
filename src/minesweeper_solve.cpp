#include <iostream>
#include <vector>
#include <list>
#define ARMA_DONT_USE_STD_MUTEX
#include <armadillo>
#include "minesweeper_class.hpp"   
#include "minesweeper_solver.hpp"

/**
 * Legacy solve function for backward compatibility.
 * This function now delegates to the new modular MinesweeperSolver class.
 * 
 * @param board Reference to the Minesweeper board to solve
 * @param x The iteration number (used for RREF skipping)
 */
void solve(MSBoard& board, int x) {
    MinesweeperSolver::solve(board, x);
}