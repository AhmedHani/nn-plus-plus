//#include <math.h>
//#include "CostFunction.h"
//
//double CostFunction::mean_squared_error(double a, double b) {
//	return pow(a - b, 2);
//}
//
//double CostFunction::mean_squared_error(double* a, double* b) {
//	return 0.0;
//}
//
//Matrix* CostFunction::mean_squared_error(Matrix* a, Matrix* b) {
//	Matrix* result = new Matrix(a->get_size(0), a->get_size(1), "zeros");
//
//	for (size_t i = 0; i < a->get_size(0); i++) {
//		for (size_t j = 0; j < a->get_size(1); j++) {
//			result->set_value(i, j, mean_squared_error(a->get_value(i, j), b->get_value(i, j)));
//		}
//	}
//
//	return result;
//}
//
//double CostFunction::mean_absolute_error(double a, double b) {
//	return abs(a - b);
//}
//
//double CostFunction::mean_absolute_error(double* a, double* b) {
//	return 0.0;
//}
//
//double CostFunction::cross_entropy(double* a, double* b) {
//	return 0.0;
//}