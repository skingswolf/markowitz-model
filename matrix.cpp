#include "matrix.h"

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
 * Multiplies each element in a matrix with a constant. Modifies matrix inplace.
 * 
 * @param matrix - The matrix to which each element will be multiplied with the constant.
 * @param scalarFunction - The scalar function.
 **/
template <typename T>
vector<vector<T> > multiplyMatrixWithConstant(vector<vector<T> > &matrix, T constant)
{
    vector<vector<double> > outputMatrix = copyMatrix(matrix);

    int numberOfRows = outputMatrix.size();
    int numberOfColumns = outputMatrix[0].size();

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfColumns; j++)
        {
            outputMatrix[i][j] = matrix[i][j] * constant;
        }
    }

    return outputMatrix;
}

/**
 * Adds the two given matrices together. 
 * 
 * @param matrix - The left component in the matrix addition.
 * @param otherMatrix - The right component in the matrix addition.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > addMatrices(vector<vector<T> > matrix, vector<vector<T> > otherMatrix)
{
    return applyBinaryOperatorToMatrices(matrix, otherMatrix, add);
}

/**
 * Subtracts the second given matrix from the first given matrix. 
 * 
 * @param matrix - The left component in the matrix subtraction.
 * @param otherMatrix - The right component in the matrix subtraction.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > subtractMatrices(vector<vector<T> > matrix, vector<vector<T> > otherMatrix)
{
    return applyBinaryOperatorToMatrices(matrix, otherMatrix, subtract);
}

/**
 * Add the two given values.
 * 
 * @param x - The left component in the addition.
 * @param y - The right component in the addition.
 * @return - The sum of the two given values
 **/
template <typename T>
T add(T x, T y)
{
    return x + y;
}

/**
 * Subtract the two given values.
 * 
 * @param x - The left component in the subtraction.
 * @param y - The right component in the subtraction.
 * @return - The subtraction of the two given values
 **/
template <typename T>
T subtract(T x, T y)
{
    return x - y;
}

/**
 * Apply the given binary operator to the two given matrices.
 * 
 * @param matrix - The left component in the binary operator.
 * @param otherMatrix - The right component in the binary operator.
 * @return The newly created matrix.
 **/
template <typename T>
vector<vector<T> > applyBinaryOperatorToMatrices(vector<vector<T> > matrix, vector<vector<T> > otherMatrix, T (*operatorFunction)(T, T))
{
    int numberOfRows = matrix.size();
    int numberOfColumns = matrix[0].size();

    int numberOfOtherMatrixRows = otherMatrix.size();
    int numberOfOtherMatrixColumns = otherMatrix[0].size();

    // Check if the dimensions of `matrix` and `otherMatrix` are
    // compatible with each other.
    if (numberOfRows != numberOfOtherMatrixRows || numberOfColumns != numberOfOtherMatrixColumns)
    {
        cout << "Matrix dimensions are not compatible for the matrix binary operation." << endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<T> > outputMatrix;

    // Allocate memory for transposedMatrix.
    outputMatrix.resize(numberOfRows);

    for (int i = 0; i < numberOfRows; i++)
    {
        outputMatrix[i].resize(numberOfColumns);

        for (int j = 0; j < numberOfColumns; j++)
        {
            outputMatrix[i][j] = operatorFunction(matrix[i][j], otherMatrix[i][j]);
        }
    }

    return outputMatrix;
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
 * Converts the given column vector to a row vector.
 * 
 * @param columnVector - The column vector to be converted.
 * @return The row vector.
 **/
template <typename T>
vector<T> convertFromColumnToRowVector(vector<vector<T> > &columnVector)
{
    int numOfElements = columnVector.size();
    vector<T> rowVector;
    rowVector.resize(numOfElements);

    for (int i = 0; i < numOfElements; i++)
    {
        rowVector[i] = columnVector[i][0];
    }

    return rowVector;
}

/**
 * Converts the given row vector to a column vector.
 * 
 * @param rowVector - The row vector to be converted.
 * @return The column vector.
 **/
template <typename T>
vector<vector<T> > convertFromRowToColumnVector(vector<T> &rowVector)
{
    int numOfElements = rowVector.size();
    vector<T> columnVector;
    columnVector.resize(numOfElements);

    for (int i = 0; i < numOfElements; i++)
    {
        vector<T> cRow;
        cRow.resize(1);
        cRow[0] = rowVector[i];
        columnVector[i] = cRow[0];
    }

    return columnVector;
}

/**
 * Returns a copy of the given matrix.
 * 
 * @param matrix - The matrix to be copied.
 * @return The copy of the matrix.
 **/
template <typename T>
vector<vector<T> > copyMatrix(vector<vector<T> > &matrix)
{
    int numberOfRows = matrix.size();
    int numberOfColumns = matrix[0].size();

    vector<vector<T> > outputMatrix;

    // Allocate memory for transposedMatrix.
    outputMatrix.resize(numberOfRows);

    for (int i = 0; i < numberOfRows; i++)
    {
        outputMatrix[i].resize(numberOfColumns);

        for (int j = 0; j < numberOfColumns; j++)
        {
            outputMatrix[i][j] = matrix[i][j];
        }
    }

    return outputMatrix;
}

/**
 * Prints a matrix of generic type "T" to STDOUT.
 * 
 * @param matrix - The matrix to be printed.
 **/
template <typename T>
void printMatrix(vector<vector<T> > &matrix)
{
    for (int rowIdx = 0; rowIdx < matrix.size(); rowIdx++)
    {
        for (int columnIdx = 0; columnIdx < matrix[rowIdx].size(); columnIdx++)
        {
            cout << matrix[rowIdx][columnIdx] << " ";
        }

        cout << endl;
    }
}

/**
 * Prints a row vector of generic type "T" to STDOUT.
 * 
 * @param rowVector - The row vector to be printed.
 **/
template <typename T>
void printRowVector(vector<T> &rowVector)
{
    for (int i = 0; i < rowVector.size(); i++)
    {
        cout << rowVector[i] << " ";
    }

    cout << endl;
}

/***************** Explicit Instantiations for use in markowitz_model.cpp *****************/

template vector<vector<double> > multiplyMatrices(vector<vector<double> > &matrix, vector<vector<double> > &otherMatrix);
template vector<vector<double> > multiplyMatrices(vector<vector<double> > &matrix, vector<double> &rowVector);
template vector<vector<double> > multiplyMatrices(vector<double> &rowVector, vector<vector<double> > &otherMatrix);
template vector<vector<double> > multiplyMatrixWithConstant(vector<vector<double> > &matrix, double constant);
template vector<vector<double> > addMatrices(vector<vector<double> > matrix, vector<vector<double> > otherMatrix);
template vector<vector<double> > subtractMatrices(vector<vector<double> > matrix, vector<vector<double> > otherMatrix);
template double add(double x, double y);
template double subtract(double x, double y);
template vector<vector<double> > applyBinaryOperatorToMatrices(vector<vector<double> > matrix, vector<vector<double> > otherMatrix, double (*operatorFunction)(double, double));
template vector<vector<double> > getMatrixTranspose(vector<vector<double> > &matrix);
template vector<double> convertFromColumnToRowVector(vector<vector<double> > &columnVector);
template vector<vector<double> > convertFromRowToColumnVector(vector<double> &rowVector);
template vector<vector<double> > copyMatrix(vector<vector<double> > &matrix);
template void printMatrix(vector<vector<double> > &matrix);
template void printRowVector(vector<double> &rowVector);