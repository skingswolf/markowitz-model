#ifndef Backtester_h
#define Backtester_h

#include <vector>
#include "portfolio_optimisation_model.h"

using namespace std;

/**
 * An abstract class for a backtester. Assesses the performance of a
 * model both in an in sample context and an out of sample context.
 **/
class Backtester
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
    virtual void evaluatePerformance(const vector<vector<double> > &returnsMatrix, PortfolioOptimisationModel &model, int inSampleSize, int outOfSampleSize) = 0;
};

#endif