#ifndef read_data_h
#define read_data_h

#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "csv.h"

using namespace std;

/**
 * Casts a string to a double.
 * 
 * @param s - The string to be converted into a double.
 * @return The newly cast double, or 0 if `s` didn't correspond to a string.
 **/
double stringToDouble(const string &s);

/**
 * Reads the asset returns from the file corresponding to `fileName` into
 * the `data` array.
 * 
 * @param fileName The name of the file to read the asset returns from.
 * @param numOfAssets - The number of rows to read from the CSV file.
 * @param numOfReturns - The number of columns to read from the CSV file.
 * @return A vector of vectors representing the returns matrix.
 **/
vector<vector<double> > readData(const string &fileName, int numOfAssets, int numOfReturns);

#endif