#ifndef matrix_h
#define matrix_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

/**
 * Returns the result of the multiplication of the two given matrices.
 * 
 * @param matrix - The left component in the matrix multiplication.
 * @param otherMatrix - The right component in the matrix multiplication.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > multiplyMatrices(vector<vector<T> > &matrix, vector<vector<T> > &otherMatrix);

/**
 * Returns the result of the multiplication of the given matrix and row vector.
 * 
 * @param matrix - The left component in the matrix multiplication.
 * @param rowVector - The right component in the matrix multiplication.
 * @return The output matrix from the multiplication.
 **/
template <typename T>

vector<vector<T> > multiplyMatrices(vector<vector<T> > &matrix, vector<T> &rowVector);
/**
 * Returns the result of the multiplication of the given row vector and matrix.
 * 
 * @param rowVector - The left component in the matrix multiplication.
 * @param otherMatrix - The right component in the matrix multiplication.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > multiplyMatrices(vector<T> &rowVector, vector<vector<T> > &otherMatrix);

/**
 * Returns the transpose of the given matrix.
 * 
 * @param matrix - The matrix to be transposed.
 * @return The transpose of the matrix.
 **/
template <typename T>
vector<vector<T> > getMatrixTranspose(vector<vector<T> > &matrix);

/**
 * Multiplies each element in a matrix with a constant.
 * 
 * @param matrix - The matrix to which each element will be multiplied with the constant.
 * @param scalarFunction - The scalar function.
 **/
template <typename T>
vector<vector<T> > multiplyMatrixWithConstant(vector<vector<T> > &matrix, T constant);

/**
 * Adds the two given matrices together. 
 * 
 * @param matrix - The left component in the matrix addition.
 * @param otherMatrix - The right component in the matrix addition.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > addMatrices(vector<vector<T> > matrix, vector<vector<T> > otherMatrix);

/**
 * Subtracts the second given matrix from the first given matrix. 
 * 
 * @param matrix - The left component in the matrix subtraction.
 * @param otherMatrix - The right component in the matrix subtraction.
 * @return The output matrix from the multiplication.
 **/
template <typename T>
vector<vector<T> > subtractMatrices(vector<vector<T> > matrix, vector<vector<T> > otherMatrix);

/**
 * Add the two given values.
 * 
 * @param x - The left component in the addition.
 * @param y - The right component in the addition.
 * @return - The sum of the two given values
 **/
template <typename T>
T add(T x, T y);

/**
 * Subtract the two given value.
 * 
 * @param x - The left component in the subtraction.
 * @param y - The right component in the subtraction.
 * @return - The subtraction of the two given values
 **/
template <typename T>
T subtract(T x, T y);

/**
 * Apply the given binary operator to the two given matrices.
 * 
 * @param matrix - The left component in the binary operator.
 * @param otherMatrix - The right component in the binary operator.
 * @return The newly created matrix.
 **/
template <typename T>
vector<vector<T> > applyBinaryOperatorToMatrices(vector<vector<T> > matrix, vector<vector<T> > otherMatrix, T (*operatorFunction)(T, T));

/**
 * Converts the given column vector to a row vector.
 * 
 * @param columnVector - The column vector to be converted.
 * @return The row vector.
 **/
template <typename T>
vector<T> convertFromColumnToRowVector(vector<vector<T> > &columnVector);

/**
 * Converts the given row vector to a column vector.
 * 
 * @param rowVector - The row vector to be converted.
 * @return The column vector.
 **/
template <typename T>
vector<vector<T> > convertFromRowToColumnVector(vector<T> &rowVector);

/**
 * Returns a copy of the given matrix.
 * 
 * @param matrix - The matrix to be copied.
 * @return The copy of the matrix.
 **/
template <typename T>
vector<vector<T> > copyMatrix(vector<vector<T> > &matrix);

/**
 * Prints a matrix of generic type "T" to STDOUT.
 * 
 * @param matrix - The matrix to be printed.
 **/
template <typename T>
void printMatrix(vector<vector<T> > &matrix);

/**
 * Prints a row vector of generic type "T" to STDOUT.
 * 
 * @param rowVector - The row vector to be printed.
 **/
template <typename T>
void printRowVector(vector<T> &rowVector);

#endif