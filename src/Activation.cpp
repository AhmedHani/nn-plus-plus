#include <math.h>
#include <iomanip>
#include <iostream>
#include "Activation.h"

double Activation::sigmoid(double value) {
	return (1 / (1 + exp(-value)));
}

Matrix* Activation::sigmoid(Matrix* values) {
	Matrix* result = new Matrix(values->get_size(0), values->get_size(1), "zeros");

	for (size_t i = 0; i < values->get_size(0); i++) {
		result->set_value(i, 0, sigmoid(values->get_value(i, 0)));
	}

	return result;
}

double Activation::signum(double value) {
	if (value < 0)
		return 0.0;
	else if (value == 0)
		return 0.0;
	else
		return 1.0;
}

double Activation::relu(double value) {
	return std::max(0.0, value);
}

double Activation::tanh(double value) {
	return tanh(value);
}

Matrix* Activation::softmax(Matrix* a) {
	Matrix* result = new Matrix(a->get_size(0), 1, "zeros");

	std::vector<double> sums;

	for (size_t i = 0; i < a->get_size(0); i++) {
		double sum = 0.0;

		for (size_t j = 0; j < a->get_size(1); j++) {
			sum += exp(a->get_value(i, j));
		}

		sums.push_back(sum);
	}

	for (size_t i = 0; i < result->get_size(0); i++) {
		for (size_t j = 0; j < result->get_size(1); j++) {
			result->set_value(i, j, exp(a->get_value(i, j)) / sums[i]);
		}
	}

	return result;
}