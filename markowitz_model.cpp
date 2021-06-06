#include "markowitz_model.h"

/***************** Public Methods *****************/

/**
 * Calculates and returns the optimatal portfolio weights for the
 * given subsection of time-indexed returns, as indicated by the
 * `returnsStartIdx` and `returnsEndIdx` values.
 * 
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @param targetReturn - The desired return to be attained by the optimal portfolio.
 * @return The optimal portfolio weights.
 **/
vector<double> MarkowitzModel::calculatePortfolioWeights(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, int targetReturn)
{
    int numberOfAssets = returnsMatrix.size();
    vector<double> weights = initialisePortfolioWeights(numberOfAssets);

    printMatrix(returnsMatrix);

    printRowVector(weights);

    return weights;
}

/***************** Private Methods *****************/

/**
 * Debugging method for checking that outputted portfolio 
 * weights sum to one.
 * 
 * @param portfolioWeights - The calculated portfolio weights.
 * @return The sum of the calculated portfolio weights.
 **/
double MarkowitzModel::sumPortfolioWeights(vector<double> &portfolioWeights)
{
    double portfolioWeightSum = 0;

    for (int i = 0; i < portfolioWeights.size(); i++)
    {
        portfolioWeightSum += portfolioWeights[i];
    }

    return portfolioWeightSum;
}

/**
 * Given the number of assets in scope, this function initialises
 * the portfolio such that it is equally weighted.
 * 
 * @param numberOfAssets - The number of assets in scope.
 * @return The equally weighted portfolio.
 **/
vector<double> MarkowitzModel::initialisePortfolioWeights(int numberOfAssets)
{
    double weight = 1 / numberOfAssets;
    vector<double> weights;

    weights.resize(numberOfAssets);

    for (int i = 0; i < numberOfAssets; i++)
    {
        weights[i] = weight;
    }

    return weights;
}
