#ifndef PortfolioOptimisationModel_h
#define PortfolioOptimisationModel_h

#include <vector>
#include "matrix.h"

using namespace std;

/**
 * An abstract class for a portfolio optimisation model. This portfolio 
 * outputted is optimised by varying the weights in the portfolio.
 **/
class PortfolioOptimisationModel
{
public:
    /**
     * Calculates and returns the optimatal portfolio weights for the
     * given subsection of time-indexed returns, as indicated by the
     * `returnsStartIdx` and `returnsEndIdx` values.
     * 
     * @param returnsMatrix - The matrix of time-indexed returns.
     * @param returnsStartIdx - The "first day" of the sample of returns.
     * @param returnsEndIdx - The "last day" of the sample of returns.
     * @param targetReturn - The desired return to be attained by the optimal portfolio.
     * @return The optimal portfolio weights.
     **/
    virtual vector<double> calculatePortfolioWeights(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, double targetReturn) = 0;
};

#endif