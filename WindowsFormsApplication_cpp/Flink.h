#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <string>
enum Flink_e{
	op,
	vector,
	matrix,
	total
};
union Flink_u {
	std::string * op;
	Vector * vec;
	Matrix * mat;
};
struct Flink
{
	Flink_e type;
	Flink * prev=nullptr;
	Flink * next=nullptr;
	Flink_u value;
	~Flink() {
		switch (type)
		{
		case op:
			delete value.op;
			break;
		case vector:
			delete value.vec;
			break;
		case matrix:
			delete value.mat;
			break;
		default:
			break;
		}
	}
};

