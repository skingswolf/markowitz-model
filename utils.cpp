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

    printMatrix(returnsMatrix);
    cout << "\n-----" << endl;

    multiplyMatrixWithConstant(returnsMatrix, 1. / 2);
    printMatrix(returnsMatrix);

    return 0;
}

/**
 * Returns the result of the multiplication of the two given matrices.
 * 
 * @param matrix - The left component in the matrix multiplication.
 * @param otherMatrix - The right component in the matrix multiplication.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > multiplyMatrices(vector<vector<T> > &matrix, vector<vector<T> > &otherMatrix)
{
    int numberOfMatrixColumns = matrix[0].size();
    int numberOfOtherMatrixRows = otherMatrix.size();

    // Check if the dimensions of `matrix` and `otherMatrix` are
    // compatible with each other.
    if (numberOfMatrixColumns != numberOfOtherMatrixRows)
    {
        cout << "Matrix dimensions are not compatible for matrix multiplication." << endl;
        exit(EXIT_FAILURE);
    }

    int numberOfRows = matrix.size();
    int numberOfColumns = otherMatrix[0].size();

    vector<vector<T> > outputMatrix;

    // Allocate memory for output matrix.
    outputMatrix.resize(numberOfRows);

    for (int i = 0; i < numberOfRows; i++)
    {
        outputMatrix[i].resize(numberOfColumns);
    }

    int numberOfElements = matrix[0].size();

    // Perform matrix multiplication.
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            outputMatrix[i][j] = 0;

            for (int k = 0; k < numberOfElements; k++)
            {
                outputMatrix[i][j] += matrix[i][k] * otherMatrix[k][j];
            }
        }
    }

    return outputMatrix;
}

/**
 * Returns the result of the multiplication of the given matrix and row vector.
 * 
 * @param matrix - The left component in the matrix multiplication.
 * @param rowVector - The right component in the matrix multiplication.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > multiplyMatrices(vector<vector<T> > &matrix, vector<T> &rowVector)
{
    vector<vector<T> > otherMatrix;
    otherMatrix.resize(1);
    otherMatrix[0] = rowVector;

    return multiplyMatrices(matrix, otherMatrix);
}

/**
 * Returns the result of the multiplication of the given row vector and matrix.
 * 
 * @param rowVector - The left component in the matrix multiplication.
 * @param otherMatrix - The right component in the matrix multiplication.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > multiplyMatrices(vector<T> &rowVector, vector<vector<T> > &otherMatrix)
{
    vector<vector<T> > matrix;
    matrix.resize(1);
    matrix[0] = rowVector;

    return multiplyMatrices(matrix, otherMatrix);
}

/**
 * Applies a scalar function to a matrix. Matrix is modified in place.
 * 
 * @param matrix - The matrix to which a scalar function will be applied.
 * @param scalarFunction - The scalar function.
 **/
template <typename T>
void applyScalarFunctionToMatrix(vector<vector<T> > &matrix, T (*scalarFunction)(T))
{
    int numberOfRows = matrix.size();
    int numberOfColumns = matrix[0].size();

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            matrix[i][j] = scalarFunction(matrix[i][j]);
        }
    }
}

/**
 * Multiplies each element in a matrix with a constant. Modifies matrix inplace.
 * 
 * @param matrix - The matrix to which each element will be multiplied with the constant.
 * @param scalarFunction - The scalar function.
 **/
template <typename T>
void multiplyMatrixWithConstant(vector<vector<T> > &matrix, T constant)
{
    int numberOfRows = matrix.size();
    int numberOfColumns = matrix[0].size();

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            matrix[i][j] = matrix[i][j] * constant;
        }
    }
}

/**
 * Returns the transpose of the given matrix.
 * 
 * @param matrix - The matrix to be transposed.
 * @return The transpose of the matrix.
 **/
template <typename T>
vector<vector<T> > getMatrixTranspose(vector<vector<T> > &matrix)
{
    int numberOfRows = matrix[0].size();
    int numberOfColumns = matrix.size();

    vector<vector<T> > matrixTranspose;

    // Allocate memory for transposedMatrix.
    matrixTranspose.resize(numberOfRows);

    for (int i = 0; i < numberOfRows; i++)
    {
        matrixTranspose[i].resize(numberOfColumns);
    }

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            matrixTranspose[i][j] = matrix[j][i];
        }
    }

    return matrixTranspose;
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
