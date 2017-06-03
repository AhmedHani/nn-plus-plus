#include "MeanSquaredError.h"

double MeanSquaredError::get_error(double a, double b) {
	return pow(a - b, 2);
}

double* MeanSquaredError::get_error(int size, double* a, double* b) {
	double* errors = new double[size];

	for (size_t i = 0; i < size; i++) {
		errors[i] = pow(a[i] - b[i], 2);
	}

	return errors;
}

Matrix* MeanSquaredError::get_error(Matrix* a, Matrix* b) {
	Matrix* result = new Matrix(a->get_size(0), a->get_size(1), "zeros");

	for (size_t i = 0; i < a->get_size(0); i++) {
		for (size_t j = 0; j < b->get_size(1); j++) {
			result->set_value(i, j, pow(a->get_value(i, j) - b->get_value(i, j), 2));
		}
	}

	return result;
}
