#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
}

bool DataManager::LoadVectorData()
{
	std::fstream fin;
	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	fin.open(FileName, std::ios::in);
	//Ū�����Ѧ^��false
	if (!fin)
	{
		return false;
	}
	else
	{
		//�аO��eŪ���V�qID
		int currentLoadVectorID = 0;
		//�w�q�V�q��ƼȦs�ܼ�
		std::vector<double> tempVectorData;
		//�w�qŪ���ɮצr��Ȧs�ܼ�
		std::string tempSring;
		//�q�ɮ�Ū���r��A�ѪR���V�q�`��
		fin >> tempSring;
		
		//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
		while (!fin.eof())
		{
			//�q�ɮ�Ū���r��
			fin >> tempSring;
			//�ѪR��V�q�аO"V"
			if (tempSring == "V")
			{
				if (currentLoadVectorID != 0)
				{
					//�w�q�Ȧs�V�q��Ƶ��c
					Vector tempVector;
					//�s�J�V�q���
					tempVector.Data = tempVectorData;
					//�w�q�V�q�ܼƦW�١A��VectorVariableIndex�ܼƧ@�W�٪�����
					std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
					//�s�J�V�q�ܼƦW��
					//�s�J�V�q
					Vectors[vectorVariableTemp] = tempVector;
					//���WVectorVariableIndex�A�H�T�O�ܼƦW�٤�����
					VectorVariableIndex++;
					//�M���V�q��ƼȦs
					tempVectorData.clear();
				}
				//���WcurrentLoadVectorID�A�аO���eŪ���V�qID
				currentLoadVectorID++;
				//�q�ɮ�Ū���r��A�ѪR���V�q����
				fin >> tempSring;
			}
			else
			{
				//Ū���V�q��ơA�ñNstring�ରdouble
				double value;
				value = (double)strtod(tempSring.c_str(), NULL);
				//�N�V�q��Ʀs�J�Ȧs
				tempVectorData.push_back(value);
			}
			
		}
		//Ū�J��J�ɮפ��̫�@�ӦV�q��T
		Vector tempVector;
		tempVector.Data = tempVectorData;
		std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
		Vectors[vectorVariableTemp] = tempVector;
		VectorVariableIndex++;
		//Ū�����\�^��false
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

