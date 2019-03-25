#include "Vector.h"
#include <exception>



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


//Vector dot(const Vector& l, const Vector& r);

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

std::map<std::string, VecFunc> VectorOps = {
	{"+", {add}},
	{"*",{mult}},
	{"Norm",{length}},
	{"Normal",{nrmlz}},
};