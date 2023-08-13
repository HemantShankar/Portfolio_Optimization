#include <iostream>
#include <vector>

// Function to calculate the inverse of a 2x2 matrix
void invert_2x2_matrix(const std::vector<std::vector<double>>& matrix, std::vector<std::vector<double>>& inverse) {
    double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    
    if (determinant == 0.0) {
        std::cerr << "Matrix is singular, cannot be inverted." << std::endl;
        return;
    }
    
    double inv_det = 1.0 / determinant;
    
    inverse[0][0] = matrix[1][1] * inv_det;
    inverse[0][1] = -matrix[0][1] * inv_det;
    inverse[1][0] = -matrix[1][0] * inv_det;
    inverse[1][1] = matrix[0][0] * inv_det;
}

// Function to multiply a matrix by a vector
std::vector<double> multiply_matrix_with_vector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    int num_rows = matrix.size();
    int num_cols = matrix[0].size();
    std::vector<double> result(num_rows, 0.0);

    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

int main() {
    // Define the number of assets
    int num_assets = 3;

    // Define the expected returns and covariance matrix (example values)
    std::vector<double> expected_returns = {0.1, 0.15, 0.12};
    std::vector<std::vector<double>> covariance_matrix = {
        {0.1, 0.02, 0.01},
        {0.02, 0.12, 0.03},
        {0.01, 0.03, 0.08}
    };

    // Define the tax rate
    double tax_rate = 0.2;

    // Construct the matrix P (covariance matrix) and vector q (linear term)
    std::vector<std::vector<double>> P = covariance_matrix;
    std::vector<double> q(num_assets);
    for (int i = 0; i < num_assets; ++i) {
        q[i] = -expected_returns[i] * (1 - tax_rate);
    }

    // Construct the equality constraint matrix A_eq and vector b_eq
    std::vector<std::vector<double>> A_eq(1, std::vector<double>(num_assets, 1.0));
    std::vector<double> b_eq = {1.0};

    // Calculate the inverse of matrix P (2x2 matrix)
    std::vector<std::vector<double>> P_inverse(2, std::vector<double>(2));
    invert_2x2_matrix(P, P_inverse);

    // Multiply P_inverse with q to get the optimal weights
    std::vector<double> optimal_weights = multiply_matrix_with_vector(P_inverse, q);

    // Normalize the optimal weights
    double total_weight = 0.0;
    for (double weight : optimal_weights) {
        total_weight += weight;
    }
    for (double &weight : optimal_weights) {
        weight /= total_weight;
    }

    // Display the results
    std::cout << "Optimal weights:" << std::endl;
    for (int i = 0; i < num_assets; ++i) {
        std::cout << "Asset " << i << ": " << optimal_weights[i] << std::endl;
    }

    return 0;
}
