# Tax_Optimization
This code is a C++ program for performing portfolio optimization based on expected returns, a covariance matrix, and a tax rate. It calculates the optimal weights for a portfolio of assets, considering a linear optimization problem with equality constraints.

## Introduction
Portfolio optimization is a crucial part of investment management, where the goal is to construct a portfolio of assets that maximizes returns or minimizes risk based on various constraints. This code demonstrates a simple example of portfolio optimization for a set of assets.

## Usage
Input Data: The code takes the following input data:

num_assets: The number of assets in the portfolio.
expected_returns: A vector containing the expected returns for each asset.
covariance_matrix: A 2D vector representing the covariance matrix between asset returns.
tax_rate: The tax rate applicable to capital gains.
Matrix Operations: The code includes functions for inverting a 2x2 matrix and multiplying a matrix with a vector, which are used in the optimization process.

Optimization: The code constructs matrices and vectors required for the optimization problem, including the covariance matrix adjusted for taxes, and solves it to find the optimal weights for the assets.

Results: The optimized asset weights are displayed as output.

## Example Input
For this example, the code uses sample values for expected returns, a covariance matrix, and a tax rate. You can modify these values in the main() function to suit your data.

Output
The code calculates and displays the optimal weights for each asset in the portfolio.

Error Handling
The code checks if the covariance matrix is singular (determinant equals 0) and handles this case by displaying an error message. It is essential to ensure that the input covariance matrix is positive definite.

Conclusion
This code provides a basic example of portfolio optimization for educational purposes. Real-world portfolio optimization involves additional complexities and constraints, such as constraints on asset weights, transaction costs, and more sophisticated optimization algorithms.
