#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
}

bool DataManager::LoadVectorData()
{
	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	std::fstream fin(FileName, std::ios::in);
	//Ū�����Ѧ^��false
	if (!fin)
	{
		return false;
	}
	else
	{
		ResetVectorData();
		int num_vectors = 0, entities = 0;
		char type = ' ';
		fin >> num_vectors;
		for (int i = 0; i < num_vectors; ++i) {
			fin >> type >> entities;
			if (type != 'V') {
				ResetVectorData();
				return false;
			}
			std::string name = "$v" + std::to_string(i);
			Vectors[name] = Vector(entities);
			Vector & target = Vectors[name];
			for (int e = 0; e < entities; ++e) {
					if (!(fin >> target[e])) {
						return false;
					}
			}
		}
		return true;
	}
}

bool DataManager::LoadMatrixData()
{
	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	std::fstream fin(FileName,std::ios::in);
	//Ū�����Ѧ^��false
	if (!fin)
	{
		return false;
	}
	else
	{
		ResetMatrixData();
		int num_matrices = 0, rows = 0, cols = 0;
		char type = ' ';
		fin >> num_matrices;
		for (int i = 0; i < num_matrices; ++i) {
			fin >> type >> rows >> cols;
			if (type != 'M') {
				ResetMatrixData();
				return false;
			}
			std::string name = "$m" + std::to_string(i);
			Matrices[name] = Matrix(rows, cols);
			Matrix & target = Matrices[name];
			for (int r = 0; r < rows; ++r) {
				for (int c = 0; c < cols; ++c) {
					if (!(fin >> target[r][c])) {
						return false;
					}
				}
			}
		}
		return true;
	}
}

std::map<std::string,Vector>& DataManager::GetVectors()
{
	return Vectors;
}

void DataManager::SetFileName(std::string fileName)
{
	FileName = fileName;
}

int priority(std::string in) {
	if (in == "+" || in == "-") {
		return 1;
	}
	else if (in == "*" || in == "/") {
		return 2;
	}
	else {
		//TODO:Error Detection
		return 0;
	}
}

void Infix2Postfix(std::vector<std::string>& fx) {
	try {
		std::vector<std::string> stack;
		std::vector<std::string> postfix;
		for (int i = 0, j = 0; i < fx.size(); i++)
		{
			std::string cur = fx[i];
			if (cur == "(") {
				stack.push_back(fx[i]);
			}
			else if (cur == "+" || cur == "-" || cur == "*" || cur == "/") {
				while (stack.size() > 0 && priority(stack.back()) > priority(cur)) {
					postfix.push_back(stack.back());
					stack.pop_back();
				}
				stack.push_back(cur);
			}
			else if (cur == ")") {
				while (stack.back() != "(")
				{
					postfix.push_back(stack.back());
					stack.pop_back();
				}
				stack.pop_back();
			}
			else {
				postfix.push_back(cur);
			}
		}
		while (stack.size()) {
			if (stack.back() == "(") throw std::exception("Lexical Error", -1);
			//TODO: Error Detection.
			postfix.push_back(stack.back());
			stack.pop_back();
		}
		fx = postfix;
	}
	catch (std::exception& e) {
		throw e;
	}
}

