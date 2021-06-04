
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "csv.h"

/**
 * Example commands to run this file:
 * 
 * g++ -c read_data.cpp 
 * g++ -c csv.cpp
 * g++ -o portfolioSolver csv.o read_data.o
 * ./portfolioSolver
 **/

double stringToDouble(const std::string &s);
void readData(double **data, string fileName);

int main(int argc, char *argv[])
{

    int numberAssets = 83;
    int numberReturns = 700;
    double **returnMatrix = new double *[numberAssets]; // a matrix to store the return data

    // Allocate memory for return data.
    for (int i = 0; i < numberAssets; i++)
    {
        returnMatrix[i] = new double[numberReturns];
    }

    // Read the data from the file and store it into the return matrix.
    // returnMatrix[i][j] will store the asset i, return j value.
    string fileName = "asset_returns_small.csv";
    readData(returnMatrix, fileName);

    // Example on how to calculate the average return.
    double mean = 0;

    for (int i = 0; i < numberAssets; i++)
    {
        mean = 0;
        for (int j = 0; j < numberReturns; j++)
        {
            double temp = returnMatrix[i][j];
            // cout << "Asset " << assetNo << ", Return " << i << "=" << temp << "\n";
            mean = mean + temp / numberReturns;
        }
    }

    // Deallocate memory.
    for (int i = 0; i < numberAssets; i++)
        delete[] returnMatrix[i];
    delete[] returnMatrix;

    return 0;
}

/**
 * Casts a string to a double.
 * 
 * @param s - The string to be converted into a double.
 * @return The newly cast double, or 0 if `s` didn't correspond to a string.
 **/
double stringToDouble(const std::string &s)
{
    std::istringstream i(s);

    double x;

    // Return 0 if the given string doesn't correspond to a double.
    if (!(i >> x))
    {
        return 0;
    }

    return x;
}

/**
 * Reads the asset returns from the file corresponding to `fileName` into
 * the `data` array.
 * 
 * @param data - an array to store the asset returns.
 * @param fileName The name of the file to read the asset returns from.
 **/
void readData(double **data, string fileName)
{
    char tmp[20];
    ifstream file(strcpy(tmp, fileName.c_str()));
    Csv csv(file);
    string line;
    if (file.is_open())
    {
        int i = 0;
        while (csv.getline(line) != 0)
        {
            for (int j = 0; j < csv.getnfield(); j++)
            {
                double temp = stringToDouble(csv.getfield(j));
                cout << "Asset " << j << ", Return " << i << "=" << temp << "\n";
                data[j][i] = temp;
            }

            cout << "------------\n";
            i++;
        }

        file.close();
    }
    else
    {
        cout << fileName << " missing\n";
        exit(0);
    }
}
