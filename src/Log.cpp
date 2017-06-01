#include <string>
#include <iostream>
#include "Log.h"

void Log::show(double value, std::string message) {
	std::cout << message << ": " << value << std::endl;
}

void Log::show(int value, std::string message) {
	std::cout << message << ": " << value << std::endl;
}

void Log::show(Matrix* matrix, std::string message) {
	std::cout << message << std::endl;

	std::cout << "Matrix Shape: (" << matrix->get_size(0) << ", " << matrix->get_size(1) << ")" << std::endl;

	for (size_t i = 0; i < matrix->get_size(0); i++) {
		std::cout << std::endl;

		for (size_t j = 0; j < matrix->get_size(1); j++) {
			std::cout << matrix->get_value(i, j) << "\t";
		}
	}
}

void Log::show(std::string value, std::string message) {
	std::cout << message << ": " << value << std::endl;
}