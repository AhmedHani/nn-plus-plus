#include "MeanAbsoluteError.h"

double MeanAbsoluteError::get_error(double a, double b) {
	return abs(a - b);
}

double* MeanAbsoluteError::get_error(int size, double* a, double* b) {
	double* errors = new double[size];

	for (size_t i = 0; i < size; i++) {
		errors[i] = abs(a[i] - b[i]);
	}

	return errors;
}

Matrix* MeanAbsoluteError::get_error(Matrix* a, Matrix* b) {
	Matrix* result = new Matrix(a->get_size(0), a->get_size(1), "zeros");

	for (size_t i = 0; i < a->get_size(0); i++) {
		for (size_t j = 0; j < b->get_size(1); j++) {
			result->set_value(i, j, abs(a->get_value(i, j) - b->get_value(i, j)));
		}
	}

	return result;
}
