#pragma once
#include<vector>
#include<string>
#include <map>
//定義向量資料結構
struct Vector
{
	std::vector<double> Data;

	const unsigned int dim() const {
		return Data.size();
	}

	double& operator [](std::size_t index) {
		return Data[index];
	}

	double operator [](std::size_t index) const{
		return Data[index];
	}
};
union VecFunc {
	void * fp;
	Vector(*one)(const Vector&);
	Vector(*two)(const Vector&, const  Vector&);
	Vector(*three)(const Vector&, const  Vector&, const Vector&);
};
extern std::map<std::string, VecFunc> VectorOps;

Vector add(const Vector& l, const Vector& r);
Vector mult(const Vector& l, const Vector& r);
Vector dot(const Vector& l, const Vector& r);
Vector length(const Vector& target);
Vector nrmlz(const Vector &r);


