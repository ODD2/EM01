#pragma once
#include "Vector.h"
struct Matrix
{
	Matrix();
	Matrix(unsigned int rows, unsigned int cols);
	unsigned int rows;
	unsigned int cols;
	Vector * Data;
	Vector& operator [](std::size_t index) {
		return Data[index];
	}
	Vector operator [](std::size_t index) const {
		return Data[index];
	}
};

