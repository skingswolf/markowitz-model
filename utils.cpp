
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
    vector<vector<double> > returnsMatrix = readData(numberOfAssets, numberOfReturns, fileName);

    int assetIdx = 0;
    int returnsStartIdx = 2;
    int returnsEndIdx = 4;
    cout << estimateMeanReturns(returnsMatrix, assetIdx, returnsStartIdx, returnsEndIdx) << endl;

    printMatrix(returnsMatrix, numberOfAssets, numberOfReturns);

    return 0;
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
double estimateMeanReturns(const vector<vector<double> > &returnsMatrix, int assetIdx, int returnsStartIdx, int returnsEndIdx)
{
    double meanReturn = 0;
    double numberOfReturns = 0;

    for (int returnsIdx = returnsStartIdx; returnsIdx <= returnsEndIdx; returnsIdx++)
    {
        meanReturn += returnsMatrix[assetIdx][returnsIdx];
        cout << returnsMatrix[assetIdx][returnsIdx] << endl;
        numberOfReturns += 1;
    }

    return meanReturn / numberOfReturns;
}

/**
 * Prints a matrix of generic type "T" to STDOUT.
 * 
 * @param matrix - The matrix to be printed.
 * @param numberOfRows - The number of rows in the matrix.
 * @param numberOfColumns - The number of columns in the matrix.
 **/
template <typename T>
void printMatrix(const T &matrix, int numberOfRows, int numberOfColumns)
{
    cout << "Printing matrix: \n";

    for (int rowIdx = 0; rowIdx < matrix.size(); rowIdx++)
    {
        for (int columnIdx = 0; columnIdx < matrix[0].size(); columnIdx++)
        {
            cout << matrix[rowIdx][columnIdx] << " ";
        }

        cout << endl;
    }
    cout << endl;
}