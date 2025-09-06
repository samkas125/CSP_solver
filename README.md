# Linear Algebra Based CSP Solver

This project implements a Linear Algebra-based solver for single-solution constraint satisfaction problems, such as Minesweeper. The codebase has been refactored into a modular, maintainable architecture with improved error handling and documentation.

## Architecture

The solver is organized into several specialized modules:

### Core Components

- **`MinesweeperSolver`**: Main orchestrator class that coordinates the solving process
- **`EquationBuilder`**: Handles identification of unrevealed squares and creation of constraint equations
- **`RREFProcessor`**: Processes Row-Reduced Echelon Form matrices to determine mine locations and safe cells
- **`TwoWayDict`**: Bidirectional dictionary for efficient mapping between board positions and equation indices
- **`SolverConstants`**: Centralized constants and configuration values

### Supporting Modules

- **`arma_helper`**: Armadillo linear algebra library wrapper functions
- **`minesweeper_class`**: Core Minesweeper board representation and game logic

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

### Solving Process

1. **Equation Formation**: The `EquationBuilder` identifies unrevealed squares adjacent to revealed cells and creates constraint equations
2. **Matrix Construction**: These equations are represented as an augmented matrix using the `arma_helper` functions
3. **Matrix Reduction**: The matrix is reduced to RREF using Armadillo's linear algebra capabilities
4. **Solution Processing**: The `RREFProcessor` analyzes the RREF matrix to determine mine locations and safe cells
5. **Iteration**: The process is repeated using newly revealed cells to form additional equations

### Key Improvements

- **Modular Design**: Each component has a single responsibility and clear interface
- **Error Handling**: Comprehensive validation and error checking throughout the solving process
- **Performance**: Optimized matrix operations and reduced unnecessary conversions
- **Maintainability**: Clear separation of concerns and extensive documentation
- **Extensibility**: Easy to add new solving strategies or modify existing ones
- **Organized Structure**: Clean separation between main source files (`src/`) and helper utilities (`include/`)
- **Build System**: Updated Makefile with proper include paths and directory structure

## File Structure

```
minesweeper/
├── src/                              # Main source files
│   ├── minesweeper_solver.hpp/cpp    # Main solver orchestrator
│   ├── minesweeper_solve.hpp/cpp     # Backward compatibility wrapper
│   ├── minesweeper_class.hpp/cpp     # Core board representation
│   └── gui.cpp                       # Graphical interface
├── include/                          # Helper and utility files
│   ├── equation_builder.hpp/cpp      # Equation creation logic
│   ├── rref_processor.hpp/cpp        # RREF processing logic
│   ├── two_way_dict.hpp/cpp          # Bidirectional dictionary
│   ├── solver_constants.hpp          # Constants and configuration
│   └── arma_helper.hpp/cpp           # Armadillo wrapper functions
├── libraries/                        # External dependencies
│   ├── armadillo-14.2.2/            # Armadillo linear algebra library
│   └── SFML-2.6.2/                  # SFML multimedia library
├── Makefile                          # Build configuration
└── README.md                         # This file
```

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

## Demo
Demo of solver showing iterative progression of board expansion:
<p align="center">
  <img src="https://github.com/user-attachments/assets/76b2934a-f0e4-4318-90e7-452c38a98372" alt="Demo" width="400">
</p>
