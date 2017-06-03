#include "MiniBatchStochasticGradientDescent.h"
#include "Operation.h"

MiniBatchStochasticGradientDescent::MiniBatchStochasticGradientDescent(double learning_rate, double momentum):
	learning_rate(learning_rate), momentum(momentum) {}

void MiniBatchStochasticGradientDescent::optimize(Matrix* batch_net, Matrix* batch_error, Matrix* &parameters) {
	Matrix* gradients = Operation::normalize(Operation::matmul(batch_net->transpose(), batch_error), (double)batch_net->get_size(0));

	parameters = Operation::add(parameters, Operation::mul(gradients, -this->learning_rate));
}