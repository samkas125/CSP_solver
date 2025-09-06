#ifndef SOLVER_CONSTANTS_HPP
#define SOLVER_CONSTANTS_HPP

namespace SolverConstants {
    // Board state values
    constexpr int UNREVEALED = -1;
    constexpr int MARKED_MINE = -2;
    
    // RREF processing constants
    constexpr int RREF_SKIP_FREQUENCY = 3;  // Skip RREF every 3rd iteration
    constexpr int RREF_SKIP_CONDITION = 2;  // When (x % 3 == 2)
    
    // Neighbor search directions (8-connected)
    constexpr int NEIGHBOR_DIRECTIONS[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},           { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };
    
    // Matrix operation constants
    constexpr double MATRIX_TOLERANCE = 1e-10;
}

#endif // SOLVER_CONSTANTS_HPP
