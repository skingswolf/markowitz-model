#ifndef MarkowitzModel_h
#define MarkowitzModel_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "portfolio_optimisation_model.h"
// #include "matrix.h"
#include "utils.h"
#include "read_data.h"

using namespace std;

/**
 * This class represents a Markowitz Model. This model identifies an 
 * optimal portfolio by vary the portfolio weights according to the
 * conjugate gradient method.
 * 
 * Weights can both positive and negative since shorting is allowed.
 **/
class MarkowitzModel : public virtual PortfolioOptimisationModel
{
private:
    // Constants used in the lagrange optimisation.
    const double lagrangeMultiplierOne = 0.1;
    const double lagrangeMultiplierTwo = 0.1;

    /**
     * Given the number of assets in scope, this function initialises
     * the portfolio such that it is equally weighted.
     * 
     * @param numberOfAssets - The number of assets in scope.
     * @return The equally weighted portfolio.
     **/
    vector<double> initialisePortfolioWeights(int numberOfAssets);

    /**
     * Debugging method for checking that outputted portfolio 
     * weights sum to one.
     * 
     * @param portfolioWeights - The calculated portfolio weights.
     * @return The sum of the calculated portfolio weights.
     **/
    double sumPortfolioWeights(vector<double> &portfolioWeights);

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
    vector<double> calculatePortfolioWeights(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, int targetReturn);
};

#endif