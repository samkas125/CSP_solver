#include <iostream>
#include <vector>
#define ARMA_DONT_USE_STD_MUTEX
#include <armadillo>
#include "arma_helper.hpp"

// Function to convert arma::mat to std::vector<std::vector<int>>
std::vector<std::vector<int>> convert_to_vector(const arma::mat& mat) {
    std::vector<std::vector<int>> vec(mat.n_rows, std::vector<int>(mat.n_cols));
    for (size_t i = 0; i < mat.n_rows; ++i) {
        for (size_t j = 0; j < mat.n_cols; ++j) {
            vec[i][j] = static_cast<int>(mat(i, j));
        }
    }
    return vec;
}

// Function to convert std::vector<std::vector<int>> to arma::mat
arma::mat convert_to_arma_mat(const std::vector<std::vector<int>>& vec) {
    size_t rows = vec.size();
    size_t cols = vec[0].size();
    arma::mat mat(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat(i, j) = (int) vec[i][j];
        }
    }

    return mat;
}

// Function to compute RREF
arma::mat compute_rref(const arma::mat& A) {
    arma::mat R = A;
    size_t lead = 0;
    size_t rowCount = R.n_rows;
    size_t columnCount = R.n_cols;

    for (size_t r = 0; r < rowCount; ++r) {
        if (lead >= columnCount) {
            return R;
        }
        size_t i = r;
        while (R(i, lead) == 0) {
            ++i;
            if (i == rowCount) {
                i = r;
                ++lead;
                if (lead == columnCount) {
                    return R;
                }
            }
        }
        R.swap_rows(i, r);
        R.row(r) = R.row(r) / R(r, lead);
        for (size_t j = 0; j < rowCount; ++j) {
            if (j != r) {
                R.row(j) -= R.row(r) * R(j, lead);
            }
        }
    }
    return R;
}
