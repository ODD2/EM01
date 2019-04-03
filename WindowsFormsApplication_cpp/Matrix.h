#pragma once
#include "Vector.h"
struct Matrix
{
	
	Matrix();
	Matrix(unsigned int rows, unsigned int cols);
	Matrix(const Matrix& mat);
	Matrix(Matrix&& mat);
	Matrix operator=(const Matrix & mat);
	~Matrix();
	//ptrs
	std::vector<Vector> * rref = nullptr;
	std::vector<Vector> * inv = nullptr;
	bool hasinv = true;
	//values
	unsigned int rows;
	unsigned int cols;
	std::vector<Vector> Data;
	Vector& operator [](std::size_t index) {
		return Data[index];
	}
	Vector operator [](std::size_t index) const {
		return Data[index];
	}
	static Matrix Identity(int n) {
		Matrix ret(n, n);
		for (int i = 0; i < n; ++i) {
			ret[i][i] = 1;
		}
		return ret;
	}
};

union MatFunc {
	void * fp;
	Matrix(*one)(const Matrix&);
	Matrix(*two)(const Matrix&, const  Matrix&);
	Matrix(*three)(const Matrix&, const  Matrix&, const Matrix&);
};

std::vector<std::vector<std::string>> solve(const Matrix &l, const Matrix &r);
int rank(Matrix &m);
Matrix addm(const Matrix & l, const Matrix & r);
Matrix subm(const Matrix & l, const Matrix & r);
Matrix multm(const Matrix & l, const Matrix & r);
Matrix transpose(const Matrix &m);
Matrix guass(Matrix &l);
Matrix inverse(Matrix &l);

extern std::map<std::string, MatFunc> MatrixOps;