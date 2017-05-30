#include "Operation.h"

Matrix* Operation::add(Matrix* a, Matrix* b) {
	validate_add_sub_dot(a, b);

	Matrix* result = new Matrix(a->get_size(0), a->get_size(1), "zeros");

	for (size_t i = 0; i < result->get_size(0); i++) {
		for (size_t j = 0; j < result->get_size(1); j++) {
			result->set_value(i, j, a->get_value(i, j) + b->get_value(i, j));
		}
	}

	return result;
}

Matrix* Operation::sub(Matrix* a, Matrix* b, bool absolute = false) {
	validate_add_sub_dot(a, b);

	Matrix* result = new Matrix(a->get_size(0), a->get_size(1), "zeros");

	for (size_t i = 0; i < result->get_size(0); i++) {
		for (size_t j = 0; j < result->get_size(1); j++) {
			absolute ? result->set_value(i, j, fabs(a->get_value(i, j) - b->get_value(i, j))) 
				: result->set_value(i, j, a->get_value(i, j) - b->get_value(i, j));
		}
	}

	return result;
}

Matrix* Operation::mul(Matrix* a, double value) {
	for (size_t i = 0; i < a->get_size(0); i++) {
		for (size_t j = 0; j < a->get_size(1); j++) {
			a->set_value(i, j, a->get_value(i, j) * value);
		}
	}

	return a;
}

Matrix* Operation::matmul(Matrix* a, Matrix* b) {
	validate_matmul(a, b);

	Matrix* result = new Matrix(a->get_size(0), b->get_size(1), "zeros");

	for (size_t i = 0; i < a->get_size(0); i++) {
		for (size_t j = 0; j < b->get_size(1); j++) {
			for (size_t k = 0; k < a->get_size(1); k++) {
				result->set_value(i, j, a->get_value(i, k) * b->get_value(k, j));
			}
		}
	}

	return result;
}

Matrix* Operation::matdot(Matrix* a, Matrix* b) {
	validate_add_sub_dot(a, b);

	Matrix* result = new Matrix(a->get_size(0), a->get_size(1), "zeros");

	for (size_t i = 0; i < a->get_size(0); i++) {
		for (size_t j = 0; j < a->get_size(1); j++) {
			result->set_value(i, j, a->get_value(i, j) * b->get_value(i, j));
		}
	}

	return result;
}

Matrix* Operation::normalize(Matrix* a, double value) {
	Matrix* result = new Matrix(a->get_size(0), a->get_size(1), "zeros");

	for (size_t i = 0; i < a->get_size(0); i++) {
		for (size_t j = 0; j < a->get_size(1); j++) {
			result->set_value(i, j, a->get_value(i, j) / value);
		}
	}

	return result;
}

double Operation::sum_squared(Matrix* a) {
	double sum = 0.0;

	for (size_t i = 0; i < a->get_size(0); i++) {
		for (size_t j = 0; j < a->get_size(1); j++) {
			sum += pow(a->get_value(i, j), 2);
		}
	}

	return sum;
}

bool Operation::validate_add_sub_dot(Matrix* a, Matrix* b) {
	if (a->get_size(0) != b->get_size(0) || a->get_size(1) != b->get_size(1)) {
		throw "Dimensions must be equal!";
	}

	return true;
}

bool Operation::validate_matmul(Matrix* a, Matrix* b) {
	if (a->get_size(0) != b->get_size(1) || a->get_size(1) != b->get_size(0)) {
		throw "Can't multply matrices with these dimensions";
	}

	return true;
}
