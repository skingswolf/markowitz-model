#include "utils.h"

/**
 * Given a vector of returns, this function calculates and returns the covariance matrix.
 * The start and end index parameters denote the (inclusive) range of returns
 * to calculate the covariance matrix for.
 * 
 * @param returnsMatrix - The matrix of returns.
 * @param returnsStartIdx - The start index of the returns.
 * @param returnsEndIdx - The end index of the returns.
 * @return The covariance matrix.
 **/
vector<vector<double> > estimateCovarianceMatrix(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx)
{
    // The number of days in the sample period (inclusive bounds - `returnsStartIdx` and `returnsEndIdx`)
    // that the covariance of returns matrix is being calculated for.
    double numberOfDays = returnsEndIdx + 1 - returnsStartIdx;

    // Number of rows and columns respectively.
    int numOfAssets = returnsMatrix.size();

    // A matrix to store the return data. The mean return at index i corresponds to
    // the average of the returns bounded by `returnsStartIdx` and `returnsEndIdx`.
    vector<double> meanReturns;
    meanReturns.resize(numOfAssets);

    // Populate mean returns vector. The entry at index `assetIdx`
    // in the vector corresponds to the average return of the returns
    // bounded by the indices `returnsStartIdx` and `returnsEndIdx`;
    for (int assetIdx = 0; assetIdx < numOfAssets; assetIdx++)
    {
        meanReturns[assetIdx] = calculateMeanReturn(returnsMatrix, assetIdx, returnsStartIdx, returnsEndIdx);
    }

    // A matrix to store the covariance data.
    vector<vector<double> > covarianceMatrix;

    // Allocate memory for covariance data.
    covarianceMatrix.resize(numOfAssets);

    for (int i = 0; i < numOfAssets; i++)
    {
        covarianceMatrix[i].resize(numOfAssets);
    }

    // Temporary variables used in covariance calculation.
    double sumOfMeanDeviationProducts, productOfMeanDeviations;

    // Populate covariance matrix.
    for (int i = 0; i < numOfAssets; i++)
    {
        for (int j = 0; j < numOfAssets; j++)
        {
            sumOfMeanDeviationProducts = 0;

            for (int k = returnsStartIdx; k <= returnsEndIdx; k++)
            {
                productOfMeanDeviations = (returnsMatrix[i][k] - meanReturns[i]) * (returnsMatrix[j][k] - meanReturns[j]);

                sumOfMeanDeviationProducts += productOfMeanDeviations;
            }

            // Assign calculated covariance value into covariance matrix.
            covarianceMatrix[i][j] = sumOfMeanDeviationProducts / (numberOfDays - 1);
        }
    }

    return covarianceMatrix;
}

/**
 * Given a vector of returns, this function calculates and returns the average return.
 * The start and end index parameters denote the (inclusive) range of returns
 * to calculate the returns for.
 * 
 * @param returnsMatrix - The matrix of returns.
 * @param returnsStartIdx - The start index of the returns.
 * @param returnsEndIdx - The end index of the returns.
 * @return The average return.
 **/
double calculateMeanReturn(const vector<vector<double> > &returnsMatrix, int assetIdx, int returnsStartIdx, int returnsEndIdx)
{
    double meanReturn = 0;
    double numOfReturns = 0;

    for (int returnsIdx = returnsStartIdx; returnsIdx <= returnsEndIdx; returnsIdx++)
    {
        meanReturn += returnsMatrix[assetIdx][returnsIdx];
        numOfReturns += 1;
    }

    return meanReturn / numOfReturns;
}

/**
 * Returns a column vector of mean returns corresponding to the time period.
 * The start and end index parameters denote the (inclusive) range of returns
 * to calculate the returns for.
 * 
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @return The column vector of mean returns.
 **/
vector<vector<double> > calculateMeanReturns(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx)
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
