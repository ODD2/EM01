#include "Vector.h"
#include <stdarg.h>
#include <exception>
#include <math.h>
#define DIM_ERR throw std::exception("Vector Dimension Error", -1);


//The Addition of Vector
Vector add(const Vector& l, const Vector& r) throw (std::exception){
	if (l.dim() != r.dim()) {
		throw std::exception("Vector Dimension Error", -1);
	}
	Vector ret = l;
	for (int i = 0, j = ret.dim(); i < j; i++) {
		ret.Data[i] += r.Data[i];
	}
	return ret;
}

//The Combination of Dot and Scale Operation
Vector mult(const Vector& l, const Vector& r) throw(std::exception){
	
	if (l.dim() == 1 || r.dim() == 1) {
		//Scale
		bool is_l = l.dim() == 1;
		Vector ret = is_l ? r : l ;
		double scale = is_l ? l.Data[0] : r.Data[0];
		for (int i = 0, ii = ret.dim(); i < ii ; ++i) {
			ret.Data[i] *= scale;
		}
		return ret;
	}
	else if (l.dim() != r.dim()) {
		throw std::exception("Vector Dimension Error", -1);
	}
	else {
		//Dot
		Vector ret;
		double ret_d = 0;
		for (int i = 0, ii = r.dim(); i < ii; ++i) {
			ret_d += l.Data[i] * r.Data[i];
		}
		ret.Data.push_back(ret_d);
		return ret;
	}
}

//The Crossproduct of Vector
Vector cross(const Vector&l, const Vector &r) throw(std::exception) {
	if (l.dim() == 3 && r.dim() == 3) {
		Vector ret(3);
		ret[2] = l[0] * r[1] - r[0]*l[1];
		ret[0] = l[1] * r[2] - r[1] * l[2];
		ret[1] = l[2] * r[0] - r[2] * l[0];
		return ret;
	}
	else {
		DIM_ERR
	}
}

//Vector dot(const Vector& l, const Vector& r);

Vector comp(const Vector&l, const Vector&r) {
	Vector cross_r =  mult(l,r);
	Vector b_leng = length(r);
	b_leng[0] = 1 / b_leng[0];
	return mult(b_leng, cross_r);
}

Vector proj(const Vector&l, const Vector&r) {
	return mult(comp(l, r), nrmlz(r));
}

Vector triangle(const Vector &l, const Vector &r) {
	Vector half(1);
	half[0] = 0.5;
	return mult(half, length(cross(l, r)));
}

//The Magnitude of a Vector
Vector length(const Vector& target) {
	double _ret = .0;
	for (int i = 0, j = target.dim(); i < j; ++i) {
		_ret += std::pow(target[i], 2);
	}
	Vector ret;
	ret.Data.push_back(std::pow(_ret, 0.5));
	return ret;
}

//Normalization of a Vector
Vector nrmlz(const Vector &r) {
	double scaler = length(r)[0];
	Vector ret = r;
	for (int i = 0, j = ret.dim(); i < j; ++i) {
		ret[i] /= scaler;
	}
	return ret;
}

Vector angle(const Vector &l, const Vector &r) {
	if (l.dim() != r.dim()) {
		Vector ret(1);
		ret[0] = std::acos(mult(l, r)[0] / (length(l)[0] * length(r)[0])) / 3.1415925 * 180;

		return ret;
	}
	else
		DIM_ERR
}

Vector planeNormal(const Vector &l, const Vector &r) {
	return nrmlz(cross(l, r));
}

bool parallel(const Vector &l,const Vector &r) {
	if (l.dim() != r.dim()) {
		DIM_ERR;
	}
	else{
		double ll = length(l)[0], lr = length(r)[0];
		if (ll == 0 || lr == 0) return false;
		double compare =ll * lr;
		if (compare == abs(mult(l,r)[0]))return true;
		else return false;
	}
}

bool orthogonal(const Vector &l, const Vector &r) {
	if (l.dim() == r.dim()) {
		Vector Dot_r = mult(l, r);
		if (Dot_r[0] != 0) {
			return false;
		}
		return true;
	}
	//else if (l.dim()==7 && r.dim()==7){
	//}
	else 
		DIM_ERR
}

bool independent(const Vector &l, const Vector &r) {
	if (!parallel(l, r)) {
		return true;
	}
	return false;
}

std::vector<Vector> gram_schmidt(std::vector<Vector> ret) {
	ret[0] = nrmlz(ret[0]);
	int dim = ret[0].dim();
	if (ret.size() < dim) {
		throw std::exception("Insufficient Vector", -1);
	}
	for (int i = 1; i < ret.size(); i++) {
		if (ret[i].dim() != dim) {
			DIM_ERR
		}
	}
	for (int i = 1; i < dim; ++i) {
		for (int j = 0; j < i; ++j) {
			Vector dot_r = mult(ret[i], ret[j]); dot_r[0] *= -1;
			ret[i] = add(ret[i], mult(dot_r, ret[j]));
		}
		ret[i] = nrmlz(ret[i]);
	}
	return ret;
}
std::vector<Vector> gram_schmidt(Vector l, ...) {
	va_list ap;
	va_start(ap, l);
	std::vector<Vector> ret(1); 	ret[0] = nrmlz(l);
	int dim = ret[0].dim();
	for (int i = 1; i < dim ; i++) {
		ret.push_back(va_arg(ap, Vector));
		if (ret.back().dim() != dim) {
			DIM_ERR
		}
	}
	for (int i = 1; i < dim; ++i) {
		for (int j = 0; j < i; ++j) {
			Vector dot_r = mult(ret[i], ret[j]); dot_r[0] *= -1;
			ret[i] = add(ret[i], mult(dot_r, ret[j]));
		}
		ret[i] = nrmlz(ret[i]);
	}
	return ret;
}

std::map<std::string, VecFunc> VectorOps = {
	{"+", {add}},
	{"*",{mult}},
	{"Norm",{length}},
	{"Normal",{nrmlz}},
};