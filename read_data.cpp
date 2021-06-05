
#include "read_data.h"

using namespace std;

/**
 * Main function here purely included to allow for debugging read data
 * functions in this file. 
 **/
// int main(int argc, char *argv[])
// {
//     // string fileName = "asset_returns.csv";
//     // int numberOfAssets = 83;
//     // int numberOfReturns = 700;

//     // string fileName = "asset_returns_small.csv";
//     // int numberOfAssets = 5;
//     // int numberOfReturns = 10;

//     string fileName = "dummy_returns.csv";
//     int numberOfAssets = 4;
//     int numberOfReturns = 5;

//     // A matrix to store the return data.
//     vector<vector<double> > returnMatrix = readData(numberOfAssets, numberOfReturns, fileName);

//     // Example on how to calculate the average return.
//     double mean = 0;

//     for (int i = 0; i < numberOfAssets; i++)
//     {
//         mean = 0;
//         for (int j = 0; j < numberOfReturns; j++)
//         {
//             double temp = returnMatrix[i][j];
//             cout << "Asset " << i << ", Return " << j << "=" << temp << "\n";
//             mean = mean + temp / numberOfReturns;
//         }

//         cout << "------------\n";
//     }

//     return 0;
// }

/**
 * Casts a string to a double.
 * 
 * @param s - The string to be converted into a double.
 * @return The newly cast double, or 0 if `s` didn't correspond to a string.
 **/
double stringToDouble(const string &s)
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
 * @param numberOfAssets - The number of rows to read from the CSV file.
 * @param numberOfReturns - The number of columns to read from the CSV file.
 * @param fileName The name of the file to read the asset returns from.
 * @return A vector of vectors representing the returns matrix.
 **/
vector<vector<double> > readData(int numberOfAssets, int numberOfReturns, const string &fileName)
{
    char tmp[20];
    ifstream file(strcpy(tmp, fileName.c_str()));
    Csv csv(file);
    string line;

    // Open file stream. If it fails, exit.
    if (!file.is_open())
    {
        cout << fileName << " missing\n";
        exit(0);
    }

    // A matrix to store the return data.
    vector<vector<double> > returnsMatrix;

    returnsMatrix.resize(numberOfAssets);

    // Allocate memory for return data.
    for (int i = 0; i < numberOfAssets; i++)
    {
        returnsMatrix[i].resize(numberOfReturns, -1);
    }

    // Read through the file line by line, reading return values into returns matrix.
    // returnsMatrix[i][j] will store the asset i, return j value.
    for (int returnIdx = 0; csv.getline(line) != 0; returnIdx++)
    {
        for (int assetIdx = 0; assetIdx < csv.getnfield(); assetIdx++)
        {
            double temp = stringToDouble(csv.getfield(assetIdx));
            // cout << "Asset " << assetIdx << ", Return " << returnIdx << "=" << temp << "\n"; // TODO
            returnsMatrix[assetIdx][returnIdx] = temp;
        }

        // cout << "------------\n"; // TODO
    }

    file.close();

    return returnsMatrix;
}
