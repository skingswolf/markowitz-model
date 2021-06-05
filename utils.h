#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <vector>
#include "read_data.h"

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
double estimateMeanReturns(const vector<vector<double> > &returnsMatrix, int assetIdx, int returnsStartIdx, int returnsEndIdx);

/**
 * Prints a matrix of generic type "T" to STDOUT.
 * 
 * @param matrix - The matrix to be printed.
 * @param numberOfRows - The number of rows in the matrix.
 * @param numberOfColumns - The number of columns in the matrix.
 **/
template <typename T>
void printMatrix(const T &matrix, int numberOfRows, int numberOfColumns);

#endif