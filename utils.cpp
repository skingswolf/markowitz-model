#include "utils.h"

using namespace std;

/**
 * Main function here purely included to allow for debugging utils
 * functions in this file. 
 **/
int main(int argc, char *argv[])
{
    string fileName = "dummy_returns.csv";
    int numberOfAssets = 4;
    int numberOfReturns = 5;

    // A matrix to store the return data.
    vector<vector<double> > returnsMatrix = readData(fileName, numberOfAssets, numberOfReturns);

    int returnsStartIdx = 0;
    int returnsEndIdx = 4;

    vector<vector<double> > covarianceMatrix = estimateCovarianceMatrix(returnsMatrix, returnsStartIdx, returnsEndIdx);

    printMatrix(covarianceMatrix);

    return 0;
}

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
    int numberOfAssets = returnsMatrix.size();

    // A matrix to store the return data. The mean return at index i corresponds to
    // the average of the returns bounded by `returnsStartIdx` and `returnsEndIdx`.
    vector<double> meanReturns;
    meanReturns.resize(numberOfAssets);

    // Populate mean returns vector. The entry at index `assetIdx`
    // in the vector corresponds to the average return of the returns
    // bounded by the indices `returnsStartIdx` and `returnsEndIdx`;
    for (int assetIdx = 0; assetIdx < numberOfAssets; assetIdx++)
    {
        meanReturns[assetIdx] = calculateMeanReturn(returnsMatrix, assetIdx, returnsStartIdx, returnsEndIdx);
    }

    // A matrix to store the covariance data.
    vector<vector<double> > covarianceMatrix;

    // Allocate memory for covariance data.
    covarianceMatrix.resize(numberOfAssets);

    for (int i = 0; i < numberOfAssets; i++)
    {
        covarianceMatrix[i].resize(numberOfAssets);
    }

    // Temporary variables used in covariance calculation.
    double sumOfMeanDeviationProducts, productOfMeanDeviations;

    // Populate covariance matrix.
    for (int i = 0; i < numberOfAssets; i++)
    {
        for (int j = 0; j < numberOfAssets; j++)
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
    double numberOfReturns = 0;

    for (int returnsIdx = returnsStartIdx; returnsIdx <= returnsEndIdx; returnsIdx++)
    {
        meanReturn += returnsMatrix[assetIdx][returnsIdx];
        numberOfReturns += 1;
    }

    return meanReturn / numberOfReturns;
}

/**
 * Prints a matrix of generic type "T" to STDOUT.
 * 
 * @param matrix - The matrix to be printed.
 **/
template <typename T>
void printMatrix(const T &matrix)
{
    for (int rowIdx = 0; rowIdx < matrix.size(); rowIdx++)
    {
        printRowVector(matrix[rowIdx]);

        cout << endl;
    }
}

/**
 * Prints a row vector of generic type "T" to STDOUT.
 * 
 * @param rowVector - The row vector to be printed.
 **/
template <typename T>
void printRowVector(const T &rowVector)
{
    for (int i = 0; i < rowVector.size(); i++)
    {
        cout << rowVector[i] << " ";
    }
}
