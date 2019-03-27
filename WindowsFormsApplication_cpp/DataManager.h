#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include <map>
#include <exception>
#include "Vector.h"
#include "Flink.h"

//�w�q���޸��class
class DataManager
{
private:
	//�x�s�V�q���
	std::map<std::string,Vector> Vectors;

	//�����V�qID�A�Ω󱱺�
	int  VectorVariableIndex;
	//�����ɮ׸��|�W��
	std::string FileName;
public:
	DataManager();
	//Ū���V�q���
	bool LoadVectorData();
	void ResetVectorData() {
		VectorVariableIndex = 0; 
		Vectors.clear();
	}
	//���o�V�q���
	std::map<std::string, Vector>& GetVectors();
	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);
};

int priority(std::string in);

void Infix2Postfix(std::vector<std::string>& fx);
