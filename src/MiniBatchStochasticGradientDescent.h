#ifndef MINI_BATCH_STOCHASTIC_GRADIENT_DESCENT_H
#define MINI_BATCH_STOCHASTIC_GRADIENT_DESCENT_H

#include <string>
#include "CostFunction.h"

class MiniBatchStochasticGradientDescent {
public:
	MiniBatchStochasticGradientDescent(double learning_rate = 0.1, double momentum = 1.0);
	void optimize(Matrix* batch_net, Matrix* batch_error, Matrix* &parameters);

private:
	double learning_rate;
	double momentum;
};

#endif