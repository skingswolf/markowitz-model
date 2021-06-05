#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <vector>
#include "read_data.h"

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
vector<vector<double> > estimateCovarianceMatrix(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx);

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
double calculateMeanReturn(const vector<vector<double> > &returnsMatrix, int assetIdx, int returnsStartIdx, int returnsEndIdx);

/**
 * Prints a matrix of generic type "T" to STDOUT.
 * 
 * @param matrix - The matrix to be printed.
 **/
template <typename T>
void printMatrix(const T &matrix);

/**
 * Prints a row vector of generic type "T" to STDOUT.
 * 
 * @param rowVector - The row vector to be printed.
 **/
template <typename T>
void printRowVector(const T &rowVector);

#endif