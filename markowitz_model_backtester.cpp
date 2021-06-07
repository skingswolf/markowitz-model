#include "markowitz_model_backtester.h"

/**
 * Evaluates the given models performance on the given data set `returnsMatrix`.
 * 
 * @param returnsMatrix - The matrix of returns.
 * @param model - The portfolio optimisation model.
 * @param inSampleSize - The window size of the insample.
 * @param outOfSampleSize - The window size of the out of sample.
 **/
void MarkowitzModelBacktester::evaluatePerformance(const vector<vector<double> > &returnsMatrix, PortfolioOptimisationModel &model, int inSampleSize, int outOfSampleSize)
{
    cout << "Running backtest" << endl;

    int numOfAssets = returnsMatrix.size();
    int numOfReturns = returnsMatrix[0].size();

    vector<double> targetReturns = initialiseTargetReturns();

    recordBacktestResults(returnsMatrix, model, targetReturns, inSampleSize, outOfSampleSize, numOfReturns);
}

/**
 * Writes out all backtest returns for different portfolios and
 * different sample period to a csv file. Each portfolio
 * corresponds to a different target return. 
 * 
 * @param returnsMatrix - The matrix of returns.
 * @param model - The portfolio optimisation model.
 * @param targetReturns - The target returns.
 * @param inSampleSize - The window size of the insample.
 * @param outOfSampleSize - The window size of the out of sample.
 * @param numOfReturns - The number of returns in scope
 **/
void MarkowitzModelBacktester::recordBacktestResults(const vector<vector<double> > &returnsMatrix, PortfolioOptimisationModel &model, vector<double> targetReturns, int inSampleSize, int outOfSampleSize, int numOfReturns)
{
    int firstInSampleDay = 0;
    int lastInSampleDay = firstInSampleDay + inSampleSize - 1;
    int firstOutOfSampleDay = firstInSampleDay + inSampleSize;
    int lastOutOfSampleDay = firstOutOfSampleDay + outOfSampleSize - 1;

    int numOfTargetReturns = targetReturns.size();
    int numOfWindows = 50; // Inferred from values of `windowIdx`;

    // Temp variables in later for loop.
    vector<double> inSampleWeights;
    vector<vector<double> > inSampleWeightsColumnVector;
    double portfolioMeanReturn = 0;

    // Dimensions are (numOfTargetReturns x windowIdx).
    vector<vector<double> > backtestingReturns;
    backtestingReturns.resize(numOfTargetReturns);

    // Dimensions are (numOfTargetReturns x windowIdx).
    vector<vector<double> > backtestingSharpeRatios;
    backtestingSharpeRatios.resize(numOfTargetReturns);

    for (int targetReturnIdx = 0; targetReturnIdx < numOfTargetReturns; targetReturnIdx++)
    {
        vector<double> backtestingReturnsRow;
        backtestingReturnsRow.resize(numOfWindows);
        backtestingReturns[targetReturnIdx] = backtestingReturnsRow;

        vector<double> backtestingSharpeRatiosRow;
        backtestingSharpeRatiosRow.resize(numOfWindows);
        backtestingSharpeRatios[targetReturnIdx] = backtestingSharpeRatiosRow;

        for (int windowIdx = 0; windowIdx < numOfWindows; windowIdx++)
        {
            inSampleWeights = model.calculatePortfolioWeights(returnsMatrix, firstInSampleDay, lastInSampleDay, targetReturns[targetReturnIdx]);
            inSampleWeightsColumnVector = convertFromRowToColumnVector(inSampleWeights);

            backtestingReturns[targetReturnIdx][windowIdx] = calculatePortfolioMeanReturn(returnsMatrix, firstOutOfSampleDay, lastOutOfSampleDay, inSampleWeightsColumnVector);
            backtestingSharpeRatios[targetReturnIdx][windowIdx] = calculateSharpeRatio(returnsMatrix, firstOutOfSampleDay, lastOutOfSampleDay, inSampleWeights);

            firstInSampleDay += outOfSampleSize;
            lastInSampleDay += outOfSampleSize;
            firstOutOfSampleDay += outOfSampleSize;
            lastOutOfSampleDay += outOfSampleSize;
        }

        // Reset sample space boundaries.
        firstInSampleDay = 0;
        lastInSampleDay = firstInSampleDay + inSampleSize - 1;
        firstOutOfSampleDay = firstInSampleDay + inSampleSize;
        lastOutOfSampleDay = firstOutOfSampleDay + outOfSampleSize - 1;
    }

    writeToCsv(backtestingReturns, targetReturns, "backtest_returns.csv", numOfTargetReturns, numOfWindows);
    writeToCsv(backtestingSharpeRatios, targetReturns, "backtest_sharpe_ratios.csv", numOfTargetReturns, numOfWindows);
}

/**
 * Writes backtest results to CSV corresponding to the given filename.
 * 
 * @param backtestResults - The backtest results.
 * @param targetReturns - The target returns.
 * @param filename - The string filename.
 * @param numOfRows - The number of rows.
 * @param numOfColumns - The number of columns.
 **/
void MarkowitzModelBacktester::writeToCsv(vector<vector<double> > backtestResults, vector<double> targetReturns, string filename, int numOfRows, int numOfColumns)
{
    ofstream resultsFile;
    resultsFile.open(filename);
    resultsFile << "Target Return"
                << ",";

    // Write out header in backtest results CSV file.
    for (int i = 0; i < numOfColumns - 1; i++)
    {
        resultsFile << i + 1 << ",";
    }
    resultsFile << endl;

    // Write out backtest returns row by row into CSV file.
    for (int i = 0; i < numOfRows; i++)
    {
        resultsFile << targetReturns[i] << ",";

        for (int j = 0; j < numOfColumns; j++)
        {
            if (j == numOfColumns - 1)
            {
                resultsFile << backtestResults[i][j];
                continue;
            }

            resultsFile << backtestResults[i][j] << ",";
        }

        resultsFile << endl;
    }

    resultsFile.close();
}

/**
 * Calculates the Sharpe Ratio of the portfolio that corresponds to the
 * given weights.
 * 
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @param weights - The portfolio weights.
 * @return The Sharpe ratio.
 **/
double MarkowitzModelBacktester::calculateSharpeRatio(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, vector<double> weights)
{
    vector<vector<double> > weightsColumnVector = convertFromRowToColumnVector(weights);
    double portfolioMeanReturn = calculatePortfolioMeanReturn(returnsMatrix, returnsStartIdx, returnsEndIdx, weightsColumnVector);
    double portfolioStandardDeviation = calculatePortfolioStandardDeviation(returnsMatrix, returnsStartIdx, returnsEndIdx, weightsColumnVector);

    return (portfolioMeanReturn - riskFreeRate) / portfolioStandardDeviation;
}

/**
 * Calculate the mean return of the portfolio that corresponds to the
 * given weights.
 * 
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @param weights - The portfolio weights in column form.
 * @return The average return of the portfolio.
 **/
double MarkowitzModelBacktester::calculatePortfolioMeanReturn(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, vector<vector<double> > weights)
{
    vector<vector<double> > assetMeanReturns = calculateMeanReturns(returnsMatrix, returnsStartIdx, returnsEndIdx);
    vector<double> assetMeanReturnsRowVector = convertFromColumnToRowVector(assetMeanReturns);
    vector<vector<double> > portfolioMeanReturn = multiplyMatrices(assetMeanReturnsRowVector, weights);

    return portfolioMeanReturn[0][0];
}

/**
 * Calculate the standard deviation of the portfolio that corresponds to the
 * given weights.
 * 
 * @param returnsMatrix - The matrix of time-indexed returns.
 * @param returnsStartIdx - The "first day" of the sample of returns.
 * @param returnsEndIdx - The "last day" of the sample of returns.
 * @param weights - The portfolio weights in column vector form.
 * @return The standard deviation of the portfolio.
 **/
double MarkowitzModelBacktester::calculatePortfolioStandardDeviation(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, vector<vector<double> > weights)
{
    vector<vector<double> > covarianceMatrix = estimateCovarianceMatrix(returnsMatrix, returnsStartIdx, returnsEndIdx);
    vector<double> weightsTranspose = convertFromColumnToRowVector(weights);

    vector<vector<double> > covarianceWeights = multiplyMatrices(covarianceMatrix, weights);
    vector<vector<double> > weightsTransposeCovarianceWeights = multiplyMatrices(weightsTranspose, covarianceWeights);

    double portfolioVariance = weightsTransposeCovarianceWeights[0][0];

    return sqrt(portfolioVariance);
}

// const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, vector<double> weightsTranspose

/**
 * Initialise target returns - i.e. values starting from zero, increasing
 * in increment of 0.005 and ending in 0.01.
 * 
 * @return The target returns.
 **/
vector<double> MarkowitzModelBacktester::initialiseTargetReturns()
{
    int numOfTargetReturns = 20;
    double value = 1. / 200;
    double increment = value;
    vector<double> targetReturns;

    for (int i = 0; i < numOfTargetReturns; i++)
    {
        targetReturns.push_back(value);
        value += increment;
    }

    return targetReturns;
}