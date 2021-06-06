#ifndef MarkowitzModel_h
#define MarkowitzModel_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "portfolio_optimisation_model.h"
#include "matrix.h"
#include "utils.h"

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
    vector<double> calculatePortfolioWeights(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, double targetReturn);

private:
    // Constants used in the lagrange optimisation.
    const double lagrangeMultiplierOne = 0.1;
    const double lagrangeMultiplierTwo = 0.1;

    // The degree of error acceptable in the conjugate gradient method.
    const double toleranceThreshold = 0.000001;

    /**
     * Calculate the beta in the conjugate gradient method.
     * 
     * @param sProduct - the scalar value s_{k+1}^T * s_{k+1}.
     * @param prevSProduct - the scalar value s_{k}^T * s_{k}.
     * @return The scalar value beta.
     **/
    double calculateBeta(double sProduct, double prevSProduct);

    /**
     * Calculate the alpha in the conjugate gradient method.
     * 
     * @param Q - The matrix Q.
     * @param p - The matrix p.
     * @param sProduct - the scalar value s^T * s.
     * @return The scalar value alpha.
     **/
    double calculateAlpha(vector<vector<double> > &Q, vector<vector<double> > &p, double sProduct);

    /**
     * Calculate the matrix multiplication of s transpose and s.
     * 
     * @param s - The matrix s. Dimensions = (numOfAssets + 2) x 1.
     * @return The scalar value s^T * s.
     **/
    double calculateSProduct(vector<vector<double> > &s);

    /**
     * Calculate the matrix Q. Consists of the covariance matrix,
     * the asset mean returns and vectors of 1.
     *
     * Dimensions: (no_of_assets + 2) x (no_of_assets + 2)
     * 
     * @param meanReturns - The mean returns vector.
     * @param returnsMatrix - The matrix of time-indexed returns.
     * @param returnsStartIdx - The "first day" of the sample of returns.
     * @param returnsEndIdx - The "last day" of the sample of returns.
     * @param numOfAssets - The number of assets in scope.
     * @return The column vector of mean returns.
     **/
    vector<vector<double> > calculateQ(const vector<vector<double> > &meanReturns, const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx, int numOfAssets);

    /**
     * Initialise the column vector x. Consists of the initial, equal
     * weights and then the lagrange multipliers.
     * 
     * Dimensions: (no_of_assets + 2) x 1
     * 
     * @param weights - The portfolio weights.
     * @param numOfAssets - The number of assets in scope.
     * @return The column vector x.
     **/
    vector<vector<double> > initialiseX(const vector<vector<double> > &weights, int numOfAssets);

    /**
     * Calculate column vector b. Consists of the zeroes and then
     * the negatives of the target return and the number one.
     * 
     * Dimensions: (no_of_assets + 2) x 1
     * 
     * @param weights - The portfolio weights.
     * @param numOfAssets - The number of assets in scope.
     * @param targetReturn - The target return of the optimised portfolio.
     * @return The column vector b.
     **/
    vector<vector<double> > calculateB(int numOfAssets, double targetReturn);

    /**
     * Returns a column vector of mean returns corresponding to the time period.
     * 
     * @param returnsMatrix - The matrix of time-indexed returns.
     * @param returnsStartIdx - The "first day" of the sample of returns.
     * @param returnsEndIdx - The "last day" of the sample of returns.
     * @return The column vector of mean returns.
     **/
    vector<vector<double> > calculateMeanReturns(const vector<vector<double> > &returnsMatrix, int returnsStartIdx, int returnsEndIdx);

    /**
     * Debugging method for checking that outputted portfolio 
     * weights sum to one.
     * 
     * @param portfolioWeights - The calculated portfolio weights.
     * @return The sum of the calculated portfolio weights.
     **/
    double sumPortfolioWeights(vector<double> &portfolioWeights);

    /**
     * Given the number of assets in scope, this function initialises
     * the portfolio such that it is equally weighted.
     * 
     * @param numOfAssets - The number of assets in scope.
     * @return The equally weighted portfolio in the form of a column vector.
     **/
    vector<vector<double> > initialisePortfolioWeights(int numOfAssets);
};

#endif