#include "markowitz_model.h"
#include "read_data.h"
#include "matrix.h"

using namespace std;

int main()
{
    // string fileName = "asset_returns.csv";
    // int numberOfAssets = 83;
    // int numberOfReturns = 700;

    // string fileName = "asset_returns_small.csv";
    // int numberOfAssets = 5;
    // int numberOfReturns = 10;

    string fileName = "dummy_returns.csv";
    int numberOfAssets = 4;
    int numberOfReturns = 5;

    // A matrix to store the return data.
    vector<vector<double> > returnMatrix = readData(fileName, numberOfAssets, numberOfReturns);

    MarkowitzModel model;
    double targetReturn = 0.005;
    int returnsStartIdx = 0;
    int returnsEndIdx = 4;

    model.calculatePortfolioWeights(returnMatrix, returnsStartIdx, returnsEndIdx, targetReturn);

    return 0;
}
