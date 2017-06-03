#include "LogisticRegression.h"
#include "Activation.h"
#include "Operation.h"
#include "Log.h"
#include "MeanSquaredError.h"
#include "MeanAbsoluteError.h"
#include "CostFunction.h"
#include "MiniBatchStochasticGradientDescent.h"
#include <iostream> 
#include <cmath>

LogisticRegression::LogisticRegression(
	double n_features, int batch_size, double learning_rate, double momentum, std::string loss_type, std::string optimizer):
	n_features(n_features), batch_size(batch_size), learning_rate(learning_rate), momentum(momentum), loss_type(loss_type), optimizer(optimizer) {
		this->weights = new Matrix(this->n_features, 1, "normal");
		this->bias = new Matrix(this->batch_size, 1, "ones");

		if (loss_type == "mse") {
			MeanSquaredError* mse = new MeanSquaredError();
			this->cost_function = mse;
		} else if (loss_type == "mae") {
			MeanAbsoluteError* mae = new MeanAbsoluteError();
			this->cost_function = mae;
		} else if (loss_type == "mce") {

		}

		if (optimizer == "sgd") {
			this->mini_batch_stochastic_gradient_descent = new MiniBatchStochasticGradientDescent(learning_rate, momentum);
		} else if (optimizer == "adam") {

		}
}

LogisticRegression::~LogisticRegression() {
	delete[] this->weights;
	delete[] this->bias;
	delete[] this->cost_function;
	delete[] this->mini_batch_stochastic_gradient_descent;
}

void LogisticRegression::fit(Matrix* features, Matrix* labels) {
	this->validate_fit(features, labels);

	Matrix* logits = Operation::add(Operation::matmul(features, this->weights), this->bias);
	Matrix* activated_logit = Activation::sigmoid(logits);
	Matrix* error = this->cost_function->get_error(labels, activated_logit);
	double error_sum = Operation::sum_squared(error);

	Log::show(Operation::round(error_sum, 4), "Current Error");

	this->mini_batch_stochastic_gradient_descent->optimize(features, error, this->weights);
	this->mini_batch_stochastic_gradient_descent->optimize(new Matrix(1, this->batch_size, "ones"), error, this->bias);
}

Matrix* LogisticRegression::predict(Matrix* features) {
	this->validate_predict(features);

	Matrix* logits = Operation::matmul(features, this->weights);
	logits = Operation::add(logits, this->bias);
	Matrix* activated_logit = Activation::sigmoid(logits);

	return activated_logit;
}

void LogisticRegression::save(std::string dir) {

}

bool LogisticRegression::validate_fit(Matrix* features, Matrix* labels) {
	if (features->get_size(0) != labels->get_size(0)) {
		throw "The number of items should be equal!";
	}

	return true;
}

bool LogisticRegression::validate_predict(Matrix* features) {
	return true;
}

void LogisticRegression::serialize() {

}
