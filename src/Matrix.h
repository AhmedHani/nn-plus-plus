#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
public:
	Matrix(int n_rows, int n_columns, std::string init);
	~Matrix();
	Matrix(double** matrix, int n_rows, int n_columns);
	double** get_matrix();
	int get_size(int axis);
	void set_value(int i, int j, double value);
	double get_value(int i, int j);
	Matrix* transpose();
	double** scale(double factor);
	std::vector<std::vector<double>> to_vector();

private:
	double** matrix;
	int n_rows;
	int n_columns;
};

#endif