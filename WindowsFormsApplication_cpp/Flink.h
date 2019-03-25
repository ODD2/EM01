#pragma once
#include "Vector.h"
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
};
struct Flink
{
	Flink_e type;
	Flink * prev=nullptr;
	Flink * next=nullptr;
	Flink_u value;
	~Flink() {
		if (type == Flink_e::op)
			delete value.op;
		else
			delete value.vec;
	}
};

