#include "markowitz_model.h"
#include "read_data.h"
#include "matrix.h"

using namespace std;

int main()
{
    string fileName = "asset_returns.csv";
    int numOfAssets = 83;
    int numOfReturns = 700;

    // string fileName = "asset_returns_small.csv";
    // int numOfAssets = 5;
    // int numOfReturns = 10;

    // // Warning - you get some ridicously weights with the CSV file.
    // // These "returns" in this file are all >> 1. Was used for debugging
    // // in the early stages of this project.
    // string fileName = "dummy_returns.csv";
    // int numOfAssets = 4;
    // int numOfReturns = 5;

    // A matrix to store the return data.
    vector<vector<double> > returnsMatrix = readData(fileName, numOfAssets, numOfReturns);

    MarkowitzModel model;
    double targetReturn = 0.005;
    int returnsStartIdx = 0;
    int returnsEndIdx = 4;

    vector<double> weights = model.calculatePortfolioWeights(returnsMatrix, returnsStartIdx, returnsEndIdx, targetReturn);

    cout << "The optimal weights are: " << endl;
    printRowVector(weights);

    return 0;
}
