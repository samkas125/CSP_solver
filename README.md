# Linear Algebra Based CSP Solver

This project implements a Linear Algebra-based solver for single-solution constraint satisfaction problems, such as Minesweeper.

## How It Works

Given a set of variables to solve for and a set of linear equations describing constraints among these variables, an augmented matrix representing the system of equations can be created. This matrix is reduced to Row-Reduced Echelon Form (RREF) to solve for valid solutions.

For single-solution problems, only equations of specific forms can be solved with certainty. Consider the equation:

$$x + y + z = n$$

There are three cases for the value of $n$:

* **$n = n_{min}$**: Here, $n = x_{min} + y_{min} + z_{min}$, where $x_{min}, y_{min}, z_{min}$ are the smallest possible values for $x, y, z$. The fixed solutions are $x_{min}, y_{min}, z_{min}$.
* **$n = n_{max}$**: This case is symmetric to $n_{min}$, with fixed solutions $x_{max}, y_{max}, z_{max}$.
* **$n_{min} < n < n_{max}$**: In this case, the values of $x, y, z$ cannot be determined with certainty if there is only one solution.

## Context: Minesweeper

Minesweeper is a classic computer game where an unrevealed grid is presented to the player. The objective is to uncover all cells that do not contain mines while avoiding the cells that do. Numbers on revealed cells indicate how many mines are adjacent to that cell, helping the player deduce the locations of mines.

### Variable Representation

In Minesweeper, each cell is represented as a variable. The value of this variable can be either 0 or 1, representing the absence or presence of a mine, respectively.

### Solving

1. **Equation Formation**: Revealed cells are used to form equations for unrevealed neighboring cells. The number of adjacent mines is used as the constraint.
2. **Matrix Construction**: These equations are represented as an augmented matrix.
3. **Matrix Reduction**: The matrix is reduced to RREF to solve for as many variables as possible using the max/min method described earlier.
4. **Iteration**: The process is repeated using newly revealed cells to form additional equations.

## Running

1. Compile the program:
   ```bash
   make
   ```
2. Run the solver:
   ```bash
   ./minesweeper_solver
   ```

## Dependencies

- **Armadillo 14.2.2**: A C++ linear algebra library.
- **SFML 2.6.2**: A multimedia library for graphical interface support.
- Ensure the libraries are located in the `libraries/` directory as specified in the `Makefile`.