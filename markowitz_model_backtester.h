#ifndef MarkowitzModelBacktester_h
#define MarkowitzModelBacktester_h

#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "backtester.h"
#include "matrix.h"
#include "utils.h"

using namespace std;

/**
 * Represents a backtester for the markowitz model. Assesses the performance of this
 * model both in an in sample context and an out of sample context.
 **/
class MarkowitzModelBacktester : public virtual Backtester
{
public:
    /**
     * Evaluates the given models performance on the given data set `returnsMatrix`.
     * 
     * @param returnsMatrix - The matrix of returns.
     * @param model - The portfolio optimisation model.
     * @param inSampleSize - The window size of the insample.
     * @param outOfSampleSize - The window size of the out of sample.
     **/
    void evaluatePerformance(const vector<vector<double> > &returnsMatrix, PortfolioOptimisationModel &model, int inSampleSize, int outOfSampleSize);

private:
    // The risk free rate used to calculate sharpe ratios.
    // Sources from UK risk free rate data between 2015 and 2019.
    const double riskFreeRate = 0.021;

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
    void recordBacktestResults(const vector<vector<double> > &returnsMatrix, PortfolioOptimisationModel &model, vector<double> targetReturns, int inSampleSize, int outOfSampleSize, int numOfReturns);

    /**
     * Writes backtest results to CSV corresponding to the given filename.
     * 
     * @param backtestResults - The backtest results.
     * @param targetReturns - The target returns.
     * @param filename - The string filename.
     * @param numOfRows - The number of rows.
     * @param numOfColumns - The number of columns.
     **/
    void writeToCsv(vector<vector<double> > backtestResults, vector<double> targetReturns, string filename, int numOfRows, int numOfColumns);

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
    double calculateSharpeRatio(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, vector<double> weights);

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
    double calculatePortfolioMeanReturn(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, vector<vector<double> > weights);

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
    double calculatePortfolioStandardDeviation(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, vector<vector<double> > weights);

    /**
     * Initialise target returns.
     * 
     * @return The target returns.
     **/
    vector<double> initialiseTargetReturns();
};

#endif