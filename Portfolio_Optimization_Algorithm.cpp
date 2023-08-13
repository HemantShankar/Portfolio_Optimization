#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Asset {
    double meanReturn;
    double stdDeviation;
};

// Objective function: Negative of portfolio variance
double calculatePortfolioVariance(const vector<double>& weights, const vector<Asset>& assets) {
    int n = weights.size();
    double portfolioVariance = 0.0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            portfolioVariance += weights[i] * weights[j] * assets[i].stdDeviation * assets[j].stdDeviation;
        }
    }

    return portfolioVariance;
}

// Constraint: Sum of weights equals 1
bool isWeightSumValid(const vector<double>& weights) {
    double sum = 0.0;
    for (double w : weights) {
        sum += w;
    }
    return fabs(sum - 1.0) < 1e-6; // Allow for small floating-point errors
}

int main() {
    vector<Asset> assets = {
        {0.1, 0.2},  // Asset 1: Mean return = 10%, Std deviation = 20%
        {0.2, 0.3},  // Asset 2: Mean return = 20%, Std deviation = 30%
        {0.15, 0.25} // Asset 3: Mean return = 15%, Std deviation = 25%
    };

    int n = assets.size();

    vector<double> initialWeights(n, 1.0 / n); // Equally weighted initial portfolio

    // Gradient descent optimization (simplified for demonstration purposes)
    const double learningRate = 0.01;
    const int maxIterations = 1000;

    vector<double> weights = initialWeights;
    for (int iter = 0; iter < maxIterations; ++iter) {
        // Calculate portfolio variance gradient
        vector<double> gradient(n, 0.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                gradient[i] += 2 * weights[j] * assets[i].stdDeviation * assets[j].stdDeviation;
            }
        }

        // Update weights using gradient descent
        for (int i = 0; i < n; ++i) {
            weights[i] -= learningRate * gradient[i];
        }

        // Enforce weight sum constraint
        if (!isWeightSumValid(weights)) {
            for (int i = 0; i < n; ++i) {
                weights[i] /= 1.0 + fabs(1.0 - weights[i]);
            }
        }
    }

    // Calculate optimized portfolio statistics
    double portfolioVariance = calculatePortfolioVariance(weights, assets);
    double portfolioReturn = 0.0;
    for (int i = 0; i < n; ++i) {
        portfolioReturn += weights[i] * assets[i].meanReturn;
    }

    cout << "Optimized Portfolio:\n";
    cout << "Weights: ";
    for (double w : weights) {
        cout << w << " ";
    }
    cout << "\nExpected Return: " << portfolioReturn << "\nPortfolio Variance: " << portfolioVariance << endl;

    return 0;
}

