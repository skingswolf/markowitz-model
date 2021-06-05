
#include "read_data.h"

using namespace std;

/**
 * Example commands to run this file:
 * 
 * g++ -c read_data.cpp 
 * g++ -c csv.cpp
 * g++ -o portfolioSolver csv.o read_data.o
 * ./portfolioSolver
 **/

int main(int argc, char *argv[])
{

    // int numberOfAssets = 83;
    // int numberOfReturns = 700;
    int numberOfAssets = 5;
    int numberOfReturns = 10;

    vector<vector<double> > returnMatrix; // a matrix to store the return data

    returnMatrix.resize(numberOfAssets);

    // Allocate memory for return data.
    for (int i = 0; i < numberOfAssets; i++)
    {
        returnMatrix[i].resize(numberOfReturns, -1);
    }

    // Read the data from the file and store it into the return matrix.
    // returnMatrix[i][j] will store the asset i, return j value.
    string fileName = "asset_returns_small.csv";
    readData(returnMatrix, fileName);

    // Example on how to calculate the average return.
    double mean = 0;

    for (int i = 0; i < numberOfAssets; i++)
    {
        mean = 0;
        for (int j = 0; j < numberOfReturns; j++)
        {
            double temp = returnMatrix[i][j];
            cout << "Asset " << i << ", Return " << j << "=" << temp << "\n";
            mean = mean + temp / numberOfReturns;
        }

        cout << "------------\n";
    }

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
void readData(vector<vector<double> > &data, string fileName)
{
    // vector<vector<double> > returnMatrix; // a matrix to store the return data

    // returnMatrix.resize(numberOfAssets);

    // // Allocate memory for return data.
    // for (int i = 0; i < numberOfAssets; i++)
    // {
    //     returnMatrix[i].resize(numberOfReturns, -1);
    // }

    char tmp[20];
    ifstream file(strcpy(tmp, fileName.c_str()));
    Csv csv(file);
    string line;

    if (!file.is_open())
    {
        cout << fileName << " missing\n";
        exit(0);
    }

    for (int returnIdx = 0; csv.getline(line) != 0; returnIdx++)
    {
        for (int assetIdx = 0; assetIdx < csv.getnfield(); assetIdx++)
        {
            double temp = stringToDouble(csv.getfield(assetIdx));
            // cout << "Asset " << assetIdx << ", Return " << returnIdx << "=" << temp << "\n";
            data[assetIdx][returnIdx] = temp;
        }

        // cout << "------------\n";
    }

    file.close();
}
