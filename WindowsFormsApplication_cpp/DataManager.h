#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include <map>
#include <exception>
#include "Vector.h"
#include "Flink.h"

//定義控管資料class
class DataManager
{
private:
	//儲存向量資料
	std::map<std::string,Vector> Vectors;

	//紀錄向量ID，用於控管
	int  VectorVariableIndex;
	//紀錄檔案路徑名稱
	std::string FileName;
public:
	DataManager();
	//讀取向量資料
	bool LoadVectorData();
	void ResetVectorData() {
		VectorVariableIndex = 0; 
		Vectors.clear();
	}
	//取得向量資料
	std::map<std::string, Vector>& GetVectors();
	//設置檔案路徑名稱
	void SetFileName(std::string fileName);
};

int priority(std::string in);

void Infix2Postfix(std::vector<std::string>& fx);
