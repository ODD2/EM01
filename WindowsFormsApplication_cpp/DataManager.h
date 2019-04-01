#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include <map>
#include <exception>
#include "Vector.h"
#include "Flink.h"
#include "Matrix.h"

//�w�q���޸��class
class DataManager
{
private:
	//�x�s�V�q���
	std::map<std::string,Vector> Vectors;
	std::map<std::string, Matrix> Matrices;
	//�����V�qID�A�Ω󱱺�
	int  VectorVariableIndex;
	//�����ɮ׸��|�W��
	std::string FileName;
public:
	DataManager();
	//Ū���V�q���
	bool LoadVectorData();
	bool LoadMatrixData();
	void ResetVectorData() {
		Vectors.clear();
	}
	void ResetMatrixData() {
		Matrices.clear();
	}
	//���o�V�q���
	std::map<std::string, Vector>& GetVectors();
	std::map<std::string, Matrix>& GetMatrices() {
		return Matrices;
	}
	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);
};

int priority(std::string in);

void Infix2Postfix(std::vector<std::string>& fx);
