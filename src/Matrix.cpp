#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <time.h>
#include <math.h>
#include "Matrix.h"

Matrix::Matrix(int n_rows, int n_columns, std::string init) {
	this->n_rows = n_rows;
	this->n_columns = n_columns;

	matrix = new double*[this->n_rows];

	for (size_t i = 0; i < this->n_rows; i++) {
		this->matrix[i] = new double[this->n_columns];
	}

	if (!init.compare("zeros")) {
		for (size_t i = 0; i < this->n_rows; i++) {
			for (size_t j = 0; j < this->n_columns; j++) {
				this->matrix[i][j] = 0.0;
			}
		}
	}

	else if (!init.compare("ones")) {
		for (size_t i = 0; i < this->n_rows; i++) {
			for (size_t j = 0; j < this->n_columns; j++) {
				this->matrix[i][j] = 1.0;
			}
		}
	}
	
	else if (!init.compare("uniform")) {
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_real_distribution<> distr(-0.1, 1.0);

		for (size_t i = 0; i < this->n_rows; i++) {
			for (size_t j = 0; j < this->n_columns; j++) {
				this->matrix[i][j] = floor(distr(generator) * 100.0 + 0.5) / 100.0;
			}
		}
	}

	else if (!init.compare("normal")) {
		std::default_random_engine de(time(0));
		std::normal_distribution<double> normal(0, 1);

		for (size_t i = 0; i < this->n_rows; i++) {
			for (size_t j = 0; j < this->n_columns; j++) {
				this->matrix[i][j] = floor(normal(de) * 100.0 + 0.5) / 100.0;;
			}
		}
	}
}

Matrix::~Matrix() {
	for (size_t i = 0; i < this->n_rows; i++) {
		delete[] this->matrix[i];
	}

	delete[] this->matrix;
}

Matrix::Matrix(double** matrix, int n_rows, int n_columns): 
	matrix(matrix), n_rows(n_rows), n_columns(n_columns) {}

double** Matrix::get_matrix() {
	return this->matrix;
}

int Matrix::get_size(int axis) {
	if (axis == 0)
		return this->n_rows;
	else if (axis == 1)
		return this->n_columns;
	else
		return 0;
}

double Matrix::get_value(int i, int j) {
	return this->matrix[i][j];
}

void Matrix::set_value(int i, int j, double value) {
	this->matrix[i][j] = value;
}

Matrix* Matrix::transpose() {
	double** transposed_matrix = new double*[this->n_columns];

	for (size_t i = 0; i < this->n_columns; i++) {
		transposed_matrix[i] = new double[this->n_rows];
	}

	for (size_t i = 0; i < this->n_rows; i++) {
		for (size_t j = 0; j < this->n_columns; j++) {
			transposed_matrix[j][i] = this->matrix[i][j];
		}
	}

	return new Matrix(transposed_matrix, this->n_columns, this->n_rows);
}

double** Matrix::scale(double factor) {
	double** modified_matrix = new double*[this->n_rows];

	for (size_t i = 0; i < this->n_rows; i++) {
		modified_matrix[i] = new double[this->n_columns];
	}

	for (size_t i = 0; i < this->n_rows; i++) {
		for (size_t j = 0; j < this->n_columns; j++) {
			modified_matrix[i][j] = factor * this->matrix[i][j];
		}
	}

	return modified_matrix;
}

std::vector<std::vector<double>> Matrix::to_vector() {
	std::vector<std::vector<double>> vector_matrix;

	for (size_t i = 0; i < this->n_rows; i++) {
		std::vector<double> row(this->matrix[i], this->matrix[i] + this->n_columns);

		vector_matrix.push_back(row);
	}

	return vector_matrix;
}