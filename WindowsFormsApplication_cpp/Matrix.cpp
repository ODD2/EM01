#include "Matrix.h"



Matrix::Matrix():rows(0),cols(0)
{
}

Matrix::Matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) {
	Data = new Vector[rows];
	for (int i = 0; i < rows; i++) {
		Data[i] = Vector(cols);
	}
}