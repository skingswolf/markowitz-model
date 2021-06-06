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
vector<double> MarkowitzModel::calculatePortfolioWeights(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, double targetReturn)
{
    int numOfAssets = returnsMatrix.size();
    cout << "number of Assets: " << numOfAssets << endl;

    vector<vector<double> > weights = initialisePortfolioWeights(numOfAssets);
    vector<vector<double> > covarianceMatrix = estimateCovarianceMatrix(returnsMatrix, returnsStartIdx, returnsEndIdx);
    vector<vector<double> > meanReturns = calculateMeanReturns(returnsMatrix, returnsStartIdx, returnsEndIdx);

    // Initialise variables for the conjugate gradient method.
    vector<vector<double> > Q = calculateQ(meanReturns, returnsMatrix, returnsStartIdx, returnsEndIdx, numOfAssets);
    vector<vector<double> > x = initialiseX(weights, numOfAssets);
    vector<vector<double> > b = calculateB(numOfAssets, targetReturn);
    vector<vector<double> > s = subtractMatrices(b, multiplyMatrices(Q, x)); // s_0 = b - Q*x_0
    vector<vector<double> > p = copyMatrix(s);

    printMatrix(s);
    cout << "-----------" << endl;
    printMatrix(p);
    cout << "-----------" << endl;

    double alpha = 0;
    double beta = 0;
    double sProduct = calculateSProduct(s); // s^T * s
    double prevSProduct = sProduct;

    cout << "s^T * s: " << sProduct << endl;
    cout << "-----------" << endl;

    // Temp variables used in conjugate gradient method.

    for (int i = 0; sProduct > toleranceThreshold; i++)
    {
        alpha = calculateAlpha(Q, p, sProduct);
        cout << alpha << endl;
        cout << "-----------" << endl;

        // TODO update s first
        beta = calculateBeta(sProduct, prevSProduct);
        cout << beta << endl;
        cout << "-----------" << endl;

        prevSProduct = sProduct;
        break;
    }
    // printMatrix(sProduct);
    // cout << "-----------" << endl;

    // printMatrix(s);
    // cout << "-----------" << endl;

    // cout << "s^T * s: " << sProduct << endl;
    // printMatrix(sProduct);
    // cout << "-----------" << endl;

    // printMatrix(Q);
    // cout << "-----------" << endl;

    // printMatrix(x);
    // cout << "-----------" << endl;
    // printMatrix(b);

    vector<double> portfolioWeights = convertFromColumnToRowVector(weights);
    // cout << sumPortfolioWeights(portfolioWeights) << endl;
    // printRowVector(portfolioWeights);

    return portfolioWeights;
}

/***************** Private Methods *****************/

/**
 * Calculate the beta in the conjugate gradient method.
 * 
 * @param sProduct - the scalar value s_{k+1}^T * s_{k+1}.
 * @param prevSProduct - the scalar value s_{k}^T * s_{k}.
 * @return The scalar value beta.
 **/
double MarkowitzModel::calculateBeta(double sProduct, double prevSProduct)
{
    return sProduct / prevSProduct;
}

/**
 * Calculate the alpha in the conjugate gradient method.
 * 
 * @param Q - The matrix Q.
 * @param p - The matrix p.
 * @param sProduct - the scalar value s^T * s.
 * @return The scalar value alpha.
 **/
double MarkowitzModel::calculateAlpha(vector<vector<double> > &Q, vector<vector<double> > &p, double sProduct)
{
    vector<vector<double> > pTranspose = getMatrixTranspose(p);
    vector<vector<double> > Qp = multiplyMatrices(Q, p);

    return multiplyMatrices(pTranspose, Qp)[0][0]; // s^T * s
}

/**
 * Calculate the matrix multiplication of s transpose and s.
 * 
 * @param s - The matrix s. Dimensions = (numOfAssets + 2) x 1.
 * @return The scalar value s^T * s.
 **/
double MarkowitzModel::calculateSProduct(vector<vector<double> > &s)
{
    vector<vector<double> > sTranspose = getMatrixTranspose(s);

    return multiplyMatrices(sTranspose, s)[0][0]; // s^T * s
}

/**
 * Calculate the matrix Q. Consists of the covariance matrix,
 * the asset mean returns and vectors of 1.
 *
 * Dimensions: (no_of_assets + 2) x (no_of_assets + 2)
 * 
 * @param meanReturns - The mean returns vector.
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @param numOfAssets - The number of assets in scope.
 * @return The column vector of mean returns.
 **/
vector<vector<double> > MarkowitzModel::calculateQ(const vector<vector<double> > &meanReturns, const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, int numOfAssets)
{
    int rank = numOfAssets + 2;

    vector<vector<double> > Q;
    Q.resize(rank);

    vector<vector<double> > covarianceMatrix = estimateCovarianceMatrix(returnsMatrix, returnsStartIdx, returnsEndIdx);

    for (int i = 0; i < rank; i++)
    {
        vector<double> qRow;
        qRow.resize(rank);

        for (int j = 0; j < rank; j++)
        {
            if (i < numOfAssets && j < numOfAssets)
            {
                qRow[j] = covarianceMatrix[i][j];
            }
            else if (j == numOfAssets && i < numOfAssets)
            {
                qRow[j] = -1 * meanReturns[i][0];
            }
            else if (i == numOfAssets && j < numOfAssets)
            {
                qRow[j] = -1 * meanReturns[j][0];
            }
            else if ((i == numOfAssets + 1 && j < numOfAssets) || (j == numOfAssets + 1 && i < numOfAssets))
            {
                qRow[j] = -1;
            }
            else
            {
                qRow[j] = 0;
            }
        }

        Q[i] = qRow;
    }

    return Q;
}

/**
 * Initialise the column vector x. Consists of the initial, equal
 * weights and then the lagrange multipliers.
 * 
 * Dimensions: (no_of_assets + 2) x 1
 * 
 * @param weights - The portfolio weights.
 * @param numOfAssets - The number of assets in scope.
 * @return The column vector x.
 **/
vector<vector<double> > MarkowitzModel::initialiseX(const vector<vector<double> > &weights, int numOfAssets)
{
    vector<vector<double> > x;
    int numOfRows = numOfAssets + 2;
    x.resize(numOfRows);

    for (int i = 0; i < numOfRows; i++)
    {
        vector<double> xRow;
        xRow.resize(1);

        if (i == numOfAssets)
        {
            xRow[0] = lagrangeMultiplierOne;
        }
        else if (i == numOfAssets + 1)
        {
            xRow[0] = lagrangeMultiplierTwo;
        }
        else
        {
            xRow[0] = weights[i][0];
        }

        x[i] = xRow;
    }

    return x;
}

/**
 * Calculate the column vector b. Consists of the zeroes and then
 * the negatives of the target return and the number one.
 * 
 * Dimensions: (no_of_assets + 2) x 1
 * 
 * @param weights - The portfolio weights.
 * @param numOfAssets - The number of assets in scope.
 * @param targetReturn - The target return of the optimised portfolio.
 * @return The column vector b.
 **/
vector<vector<double> > MarkowitzModel::calculateB(int numOfAssets, double targetReturn)
{
    vector<vector<double> > b;
    int numOfRows = numOfAssets + 2;
    b.resize(numOfRows);

    for (int i = 0; i < numOfRows; i++)
    {
        vector<double> bRow;
        bRow.resize(1);

        if (i == numOfAssets)
        {
            bRow[0] = -1 * targetReturn;
        }
        else if (i == numOfAssets + 1)
        {
            bRow[0] = -1;
        }
        else
        {
            bRow[0] = 0;
        }

        b[i] = bRow;
    }

    return b;
}

/**
 * Returns a column vector of mean returns corresponding to the time period.
 * 
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @return The column vector of mean returns.
 **/
vector<vector<double> > MarkowitzModel::calculateMeanReturns(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx)
{
    int numOfAssets = returnsMatrix.size();

    vector<vector<double> > meanReturns;
    meanReturns.resize(numOfAssets);

    for (int i = 0; i < numOfAssets; i++)
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
 * @param numOfAssets - The number of assets in scope.
 * @return The equally weighted portfolio in the form of a column vector.
 **/
vector<vector<double> > MarkowitzModel::initialisePortfolioWeights(int numOfAssets)
{
    double equalWeight = 1. / numOfAssets;
    vector<vector<double> > weights;

    weights.resize(numOfAssets);

    for (int i = 0; i < numOfAssets; i++)
    {
        vector<double> weight;
        weight.resize(1);
        weight[0] = equalWeight;

        weights[i] = weight;
    }

    return weights;
}
