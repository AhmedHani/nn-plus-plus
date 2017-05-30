#include "LogisticRegression.h"
#include "Activation.h"
#include "Operation.h"

LogisticRegression::LogisticRegression(double n_features, int batch_size, double learning_rate, double momentum, std::string loss_type):
	n_features(n_features), batch_size(batch_size), learning_rate(learning_rate), momentum(momentum), loss_type(loss_type) {
		this->weights = new Matrix(this->n_features, 1, "normal");
		this->bias = new Matrix(this->batch_size, 1, "ones");
		
}

LogisticRegression::~LogisticRegression() {
	delete[] this->weights;
}

void LogisticRegression::fit(Matrix* features, Matrix* labels) {
	this->validate_fit(features, labels);

	Matrix* logits = Operation::add(Operation::matmul(features, this->weights), this->bias);
	Matrix* activated_logit = Activation::sigmoid(logits);
	Matrix* error = CostFunction::mean_squared_error(labels, activated_logit);
	double error_sum = Operation::sum_squared(error);
	Matrix* gradients = Operation::normalize(Operation::matmul(features->transpose(), error), (double)this->batch_size);

	this->update(gradients);
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

void LogisticRegression::update(Matrix* gradients) {
	this->weights = Operation::add(this->weights, Operation::mul(gradients, -this->learning_rate));
}
