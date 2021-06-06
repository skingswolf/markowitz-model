#include "markowitz_model.h"
#include "read_data.h"
#include "matrix.h"

using namespace std;

int main()
{
    // string fileName = "asset_returns.csv";
    // int numOfAssets = 83;
    // int numOfReturns = 700;

    // string fileName = "asset_returns_small.csv";
    // int numOfAssets = 5;
    // int numOfReturns = 10;

    string fileName = "dummy_returns.csv";
    int numOfAssets = 4;
    int numOfReturns = 5;

    // A matrix to store the return data.
    vector<vector<double> > returnMatrix = readData(fileName, numOfAssets, numOfReturns);

    MarkowitzModel model;
    double targetReturn = 0.005;
    int returnsStartIdx = 0;
    int returnsEndIdx = 4;

    model.calculatePortfolioWeights(returnMatrix, returnsStartIdx, returnsEndIdx, targetReturn);

    return 0;
}
