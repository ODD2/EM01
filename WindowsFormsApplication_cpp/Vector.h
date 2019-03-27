#pragma once
#include<vector>
#include<string>
#include <map>
//定義向量資料結構
struct Vector
{
	std::vector<double> Data;
	Vector() {

	}
	Vector(int dimension):Data(dimension) {
		
	}

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
Vector cross(const Vector&l, const Vector &r);
Vector comp(const Vector&l, const Vector&r);
Vector proj(const Vector&l, const Vector&r);
Vector triangle(const Vector &l, const Vector &r);
Vector angle(const Vector &l, const Vector &r);
Vector planeNormal(const Vector &l, const Vector &r);
Vector length(const Vector& target);
Vector nrmlz(const Vector &r);
bool parallel(const Vector &l,const Vector &r);
bool orthogonal(const Vector &l, const Vector &r);
bool independent(const Vector &l, const Vector &r);
std::vector<Vector> gram_schmidt(std::vector<Vector> ret);
std::vector<Vector> gram_schmidt(Vector l, ...);



