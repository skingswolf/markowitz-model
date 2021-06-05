#ifndef read_data_h
#define read_data_h

#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "csv.h"

/**
 * Casts a string to a double.
 * 
 * @param s - The string to be converted into a double.
 * @return The newly cast double, or 0 if `s` didn't correspond to a string.
 **/
double stringToDouble(const std::string &s);

/**
 * Reads the asset returns from the file corresponding to `fileName` into
 * the `data` array.
 * 
 * @param data - an array to store the asset returns.
 * @param fileName The name of the file to read the asset returns from.
 **/
void readData(vector<vector<double> > &data, string fileName);

#endif