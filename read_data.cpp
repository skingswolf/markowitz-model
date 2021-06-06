
#include "read_data.h"

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
 * @param fileName The name of the file to read the asset returns from.
 * @param numOfAssets - The number of rows to read from the CSV file.
 * @param numOfReturns - The number of columns to read from the CSV file.
 * @return A vector of vectors representing the returns matrix.
 **/
vector<vector<double> > readData(const string &fileName, int numOfAssets, int numOfReturns)
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

    returnsMatrix.resize(numOfAssets);

    // Allocate memory for return data.
    for (int i = 0; i < numOfAssets; i++)
    {
        returnsMatrix[i].resize(numOfReturns, -1);
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
