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
    cout << "number of Assets: " << numberOfAssets << endl;
    vector<vector<double> > weights = initialisePortfolioWeights(numberOfAssets);

    printMatrix(returnsMatrix);
    cout << "-----------" << endl;

    vector<vector<double> > covarianceMatrix = estimateCovarianceMatrix(returnsMatrix, returnsStartIdx, returnsEndIdx);
    vector<vector<double> > qPartOne = multiplyMatrices(covarianceMatrix, weights);

    vector<vector<double> > meanReturns = calculateMeanReturnsVector(returnsMatrix, returnsStartIdx, returnsEndIdx);
    printMatrix(meanReturns);

    vector<double> portfolioWeights = convertFromColumnToRowVector(weights);
    // cout << sumPortfolioWeights(portfolioWeights) << endl;
    // printRowVector(portfolioWeights);

    return portfolioWeights;
}

/***************** Private Methods *****************/

/**
 * Initialise the column vector x. Consists of the initial, equal
 * weights and then the lagrange multipliers.
 * 
 * Dimensions: (no_of_assets + 2) x 1
 * 
 * @param numberOfAssets - The number of assets in scope.
 * @return The column vector x.
 **/
vector<vector<double> > initialiseX(int numberOfAssets)
{
}

/**
 * Initialise the column vector b. Consists of the zeroes and then
 * the negatives of the target return and the number one.
 * 
 * Dimensions: (no_of_assets + 2) x 1
 * 
 * @param weights - The portfolio weights.
 * @param numberOfAssets - The number of assets in scope.
 * @return The column vector b.
 **/
vector<vector<double> > initialiseB(const vector<vector<double> > &weights, int numberOfAssets)
{
    vector<vector<double> > b;
    int numOfRows =
        b.resize(numberOfAssets + 2);

    for (int i = 0; i < numberOfAssets + 2; i++)
    {
        vector<double> meanReturn;
        meanReturn.resize(1);
        meanReturn[0] = weights[0][i];
        meanReturns[i] = meanReturn;
    }

    return meanReturns;
}

/**
 * Returns a column vector of mean returns corresponding to the time period.
 * 
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @return The column vector of mean returns.
 **/
vector<vector<double> > MarkowitzModel::calculateMeanReturnsVector(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx)
{
    int numberOfAssets = returnsMatrix.size();

    vector<vector<double> > meanReturns;
    meanReturns.resize(numberOfAssets);

    for (int i = 0; i < numberOfAssets; i++)
    {
        vector<double> meanReturn;
        meanReturn.resize(1);
        meanReturn[0] = calculateMeanReturn(returnsMatrix, i, returnsStartIdx, returnsEndIdx);
        meanReturns[i] = meanReturn;
    }

    return meanReturns;
}

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
 * @return The equally weighted portfolio in the form of a column vector.
 **/
vector<vector<double> > MarkowitzModel::initialisePortfolioWeights(int numberOfAssets)
{
    double equalWeight = 1. / numberOfAssets;
    vector<vector<double> > weights;

    weights.resize(numberOfAssets);

    for (int i = 0; i < numberOfAssets; i++)
    {
        vector<double> weight;
        weight.resize(1);
        weight[0] = equalWeight;

        weights[i] = weight;
    }

    return weights;
}
