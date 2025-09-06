#include <vector>
#include <armadillo>

std::vector<std::vector<int>> convert_to_vector(const arma::mat& mat);
arma::mat convert_to_arma_mat(const std::vector<std::vector<int>>& vec);
arma::mat compute_rref(const arma::mat& A);