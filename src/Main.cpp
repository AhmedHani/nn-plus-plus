#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

	// code looks much better dealing with matrix as a normal variable
	Matrix matrix(3, 3, "zeroes");

	matrix[1][2] = 8.0;

	cout << matrix[2][2] << endl;
	cout << matrix[1][2] << endl;

	// doesn't necessarily look as good when it's a pointer
	Matrix* ptr_matrix = new Matrix(3, 3, "ones");
	
	(*ptr_matrix)[1][2] = 7.0;

	cout << (*ptr_matrix)[2][2] << endl;
	cout << (*ptr_matrix)[1][2] << endl;



	return 0;
}
