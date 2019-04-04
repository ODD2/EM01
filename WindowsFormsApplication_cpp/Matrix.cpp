#include "Matrix.h"
#include <stdarg.h>
#include <exception>
#include <math.h>
#define DIM_ERR throw std::exception("Matrix Dimension Error", -1);
#define WID_ERR throw std::exception("Matrix Width Error", -1);
#define CON_ERR throw std::exception("Matrix Constraint Error",-1);
#define SQR_ERR throw std::exception("Matrix Not Square",-1);
#define DET_ERR throw std::exception("Matrix No Determinant",-1);
#define NO_INVERSE throw std::exception("No Inverse for this Matrix",-1);
#define _ERR(x) throw std::exception(x,-1);
#define ZERO 0.0000001
typedef std::pair<int, std::pair<Vector, Vector>> IVV;

Matrix::Matrix():rows(0),cols(0)
{
}

Matrix::Matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols),Data(rows) {
	for (int i = 0; i < rows; i++) {
		Data[i] = Vector(cols);
	}
}

//copy constructor
Matrix::Matrix(const Matrix& mat) {
	Data = mat.Data;
	rows = mat.rows;
	cols = mat.cols;
	det = mat.det;
	noinv = mat.noinv;
	if (mat.rref != nullptr) {
		rref = new std::vector<Vector>(*(mat.rref));
	}
	if (mat.inv != nullptr) {
		inv = new std::vector<Vector>(*(mat.inv));
	}
}

//move constructor
Matrix::Matrix(Matrix&& mat) {
	if (&mat != this) {
		Data = std::move(mat.Data);
		rows = mat.rows;
		cols = mat.cols;
		det = mat.det;
		noinv = mat.noinv;
		if (mat.rref != nullptr) {
			rref = mat.rref;
			mat.rref = nullptr;
		}
		if (mat.inv != nullptr) {
			inv = mat.inv;
			mat.inv = nullptr;
		}
	}
}

Matrix Matrix::operator=(const Matrix & mat) {
	Data = mat.Data;
	rows = mat.rows;
	cols = mat.cols;
	det = mat.det;
	noinv = mat.noinv;
	if (mat.rref != nullptr) {
		rref = new std::vector<Vector>(*(mat.rref));
	}
	if (mat.inv != nullptr) {
		inv = new std::vector<Vector>(*(mat.inv));
	}
	return *this;
}

Matrix::~Matrix() {
	if (rref != nullptr) {
		delete rref;
	}
	if (inv != nullptr) {
		delete inv;
	}
}

Matrix addm(const Matrix & l, const Matrix & r) {
	if (l.rows != r.rows) DIM_ERR
	else if ( l.cols != r.cols) WID_ERR
	else {
		Matrix ret = l;
		for (int i = 0, j = ret.rows; i < j; ++i) {
			for (int k = 0, l = ret.cols; k < l; ++k) {
				ret[i][k] += r[i][k];
			}
		}
		return ret;
	}
}

Matrix subm(const Matrix & l, const Matrix & r) {
	if (l.rows != r.rows) DIM_ERR
	else if (l.cols != r.cols) WID_ERR
	else {
		Matrix ret = l;
		for (int i = 0, j = ret.rows; i < j; ++i) {
			for (int k = 0, l = ret.cols; k < l; ++k) {
				ret[i][k] -= r[i][k];
			}
		}
		return ret;
	}
}

Matrix multm(const Matrix & l, const Matrix & r) {
	if (l.cols != r.rows) CON_ERR
	else {
		Matrix ret(l.rows, r.cols);
		for (int retc = 0; retc < ret.cols; ++retc) {
			for (int retr = 0; retr < ret.rows; ++retr) {
				ret[retr][retc] = 0;
				for (int lc = 0; lc < l.cols; ++lc) {
					ret[retr][retc] += l[retr][lc] * r[lc][retc];
				}
			}
		}
		return ret;
	}
}

Matrix transpose(const Matrix &m) {
	Matrix ret(m.cols, m.rows);
	for (int r = 0; r < m.rows; ++r) {
		for (int c = 0; c < m.cols; ++c) {
			ret[c][r] = m[r][c];
		}
	}
	return ret;
}

int rank(Matrix &m) {
	int rk = 0;
	if (m.rref == nullptr) {
		guass(m);
	}
	std::vector<Vector> * rref = m.rref;
	for (int r = 0; r < m.rows; ++r) {
		Vector & rowVec = (*rref)[r];
		for (int c = 0; c < m.cols; ++c) {
			if (rowVec[c] != 0) {
				rk += 1;
				break;
			}
		}
	}
	return rk;
}

int comp_1(const void * a,const  void * b) {
	return ((std::pair<int, Vector>*)a)->first  -  ((std::pair<int, Vector>*)b)->first;
}

Matrix guass(Matrix &l) {
	int COLS = l.cols;
	int ROWS = l.rows;
	Matrix sortedM; sortedM.rows = l.rows;  sortedM.cols = l.cols;
	if (l.rref!=nullptr) {
		sortedM.Data = *l.rref;
		return sortedM;
	}
	//Sort
	std::vector<std::pair<int, Vector>> sorted;
	for (int i = 0; i < l.rows; ++i) {
		bool insert = false;
		for (int j = 0; j < l.cols; ++j) {
			if (fabs(l[i][j]) > ZERO) {
				std::pair<int, Vector> entity(j, l[i]);
				for (int k = 0, lk = sorted.size(); k < lk; ++k) {
					if (j < sorted[k].first) {
						sorted.insert(sorted.begin() + k, std::move(entity));
						insert = true;
						break;
					}
				}
				if (!insert) {
					sorted.push_back(std::move(entity));
					insert = true;
				}
				break;
			}
			else l[i][j] = 0;
		}
		if (!insert) {
			sorted.push_back(std::pair<int, Vector>(l.cols, l[i]));
		}
	}

	
	//Elimination
	int limit = l.rows < l.cols ? l.rows : l.cols;
	for (int r = 0; r < limit; ++r) {
		
		//Skipping leading zeros
		Vector & rowVec = sorted[r].second;
		int c = sorted[r].first;
		if (c == COLS)break;
		//Normalize
		double divident = rowVec[c];
		for (int i_c = c; i_c <COLS; ++i_c) {
			rowVec[i_c] /= divident;
		}
		//Eliminate
		for (int i_r = r + 1; i_r < ROWS; ++i_r) {
			Vector & _rowVec = sorted[i_r].second;
			double multiplier = _rowVec[c];
			if (multiplier == 0) {
				//Afterward vectors  has larger equal leading zeros.
				break;
			}
			bool leadZero = true;
			for (int i_c = c; i_c < COLS; ++i_c) {
				_rowVec[i_c] -= multiplier * rowVec[i_c];
				//Deviation Removal
				if (fabs(_rowVec[i_c]) < ZERO) {
					_rowVec[i_c] = 0.0;
					if(leadZero) sorted[i_r].first += 1;
				}
				else leadZero = false;
			}
		}

		//Sort
		if(r + 1 != ROWS )	std::qsort(&sorted[r + 1], ROWS - 1 - r, sizeof(std::pair<int, Vector>), comp_1);
	}

	//CleanUp
	for (int i_r = ROWS - 1; i_r >= 0; --i_r) {
		if (sorted[i_r].first == COLS) continue;
		Vector & base = sorted[i_r].second;
		int leading0 = sorted[i_r].first;
		for (int i_rr = i_r - 1; i_rr >= 0; --i_rr) {
			Vector & target = sorted[i_rr].second;
			double multiplier = target[leading0];
			//Deviation Removal & Multiplier Zero
			if (fabs(multiplier) < ZERO) {
				target[leading0] = 0;
				continue;
			}
			for (int i_c = leading0; i_c < COLS; ++i_c) {
				target[i_c] -= multiplier * base[i_c];
				//Deviation Removal
				if (fabs(target[i_c]) < ZERO) {
					target[i_c] = 0;
				}
			}
		}
	}


	//Create Result
	for (int i = 0; i < sorted.size(); ++i) {
		sortedM.Data.push_back(std::move(sorted[i].second));
	}
	//Save RREF for further use.
	l.rref = new std::vector<Vector>(sortedM.Data);
	return sortedM;
}

std::vector<std::vector<std::string>> solve(const Matrix &l, const Matrix &r) {
	int COLS = l.cols;
	int ROWS = l.rows;
	int ACOLS = r.cols;
	int AROWS = r.rows;
	if(ROWS!=AROWS)CON_ERR

	//Sort
	std::vector<IVV> sorted;
	for (int i = 0; i < ROWS; ++i) {
		bool insert = false;
		IVV entity; entity.second.first = l[i]; entity.second.second = r[i];
		for (int j = 0; j < COLS; ++j) {
			if (fabs(l[i][j]) > ZERO) {
				entity.first = j;
				for (int k = 0, lk = sorted.size(); k < lk; ++k) {
					if (j < sorted[k].first) {
						sorted.insert(sorted.begin() + k, std::move(entity));
						insert = true;
						break;
					}
				}
				if (!insert) {
					sorted.push_back(std::move(entity));
					insert = true;
				}
				break;
			}
			else l[i][j] = 0;
		}
		if (!insert) {
			entity.first = COLS;
			sorted.push_back(std::move(entity));
		}
	}

	//Elimination
	int limit = ROWS < COLS ? ROWS : COLS;
	for (int r = 0; r < limit; ++r) {
		
		//Skipping leading zeros
		Vector & rowVec = sorted[r].second.first;
		Vector & ansVec = sorted[r].second.second;
		int c = sorted[r].first;
		if (c == COLS)break;
		//Normalize
		double divident = rowVec[c];
		for (int i_c = c; i_c < COLS; ++i_c) {
			rowVec[i_c] /= divident;
		}
		for (int i_c = 0; i_c < ACOLS; ++i_c) {
			ansVec[i_c] /= divident;
		}
		//Eliminate
		for (int i_r = r + 1; i_r < ROWS; ++i_r) {
			Vector & _rowVec = sorted[i_r].second.first;
			Vector & _ansVec = sorted[i_r].second.second;
			
			double multiplier = _rowVec[c];
			if (multiplier == 0) {
				//Afterward vectors  has larger equal leading zeros.
				break;
			}
			bool leadZero = true;
			for (int i_c = c; i_c < COLS; ++i_c) {
				_rowVec[i_c] -= multiplier * rowVec[i_c];
				//Deviation Removal
				if (fabs(_rowVec[i_c]) < ZERO) {
					_rowVec[i_c] = 0.0;
					if (leadZero) sorted[i_r].first += 1;
				}
				else leadZero = false;
			}
			for (int i_c = 0; i_c < ACOLS; ++i_c) {
				_ansVec[i_c] -= multiplier * ansVec[i_c];
				//Deviation Removal
				if (fabs(_ansVec[i_c]) < ZERO) {
					_ansVec[i_c] = 0.0;
				}
			}
		}

		//Sort
		if (r + 1 != ROWS)	std::qsort(&sorted[r + 1], ROWS - 1 - r, sizeof(IVV), comp_1);
	}

	//CleanUp
	for (int i_r = ROWS - 1; i_r >= 0; --i_r) {
		if (sorted[i_r].first == COLS) continue;

		Vector & rowVec = sorted[i_r].second.first;
		Vector & ansVec = sorted[i_r].second.second;
		int leading0 = sorted[i_r].first;

		for (int i_rr = i_r - 1; i_rr >= 0; --i_rr) {
			Vector & _rowVec = sorted[i_rr].second.first;
			Vector & _ansVec = sorted[i_rr].second.second;
			double multiplier = _rowVec[leading0];
			//Deviation Removal & Multiplier Zero
			if (fabs(multiplier) < ZERO) {
				_rowVec[leading0] = 0;
				continue;
			}
			for (int i_c = leading0; i_c < COLS; ++i_c) {
				_rowVec[i_c] -= multiplier * rowVec[i_c];
				//Deviation Removal
				if (fabs(_rowVec[i_c]) < ZERO) {
					_rowVec[i_c] = 0;
				}
			}
			for (int i_c = 0; i_c < ACOLS; ++i_c) {
				_ansVec[i_c] -= multiplier * ansVec[i_c];
				//Deviation Removal
				if (fabs(_ansVec[i_c]) < ZERO) {
					_ansVec[i_c] = 0;
				}
			}
		}
	}

	//Create Result
	std::vector<std::vector<std::string>> result;
	for (int c = 0; c < ACOLS; ++c) {
		std::vector<std::string> ans;
		for (int r = 0; r < AROWS; ++r) {
			std::string formula;
			Vector & reqVec = sorted[r].second.first;
			for (int ac = 0; ac < COLS; ++ac) {
				if (reqVec[ac] != 0) {
					if (formula.size() != 0) {
						formula += "+";
					}
					formula += std::to_string(reqVec[ac]) + "*(x" + std::to_string(ac)+")";
				}
			}
			double value = sorted[r].second.second[c];
			if (formula.size() == 0) {
				if (value != 0) {
					ans.clear();
					ans.push_back("undefined");
					break;
				}
			}
			else  {
				ans.push_back(formula + " = " + std::to_string(value));
			}
		}
		result.push_back(std::move(ans));
	}
	return result;
}

//CAUTION!!! This Function Deals ONLY SQUARE Matrices.
Matrix inverse( Matrix &l) {
	//Deal only square matrices
	if(l.rows!=l.cols) SQR_ERR
	//If singular
	else if(l.noinv) NO_INVERSE
	//If generated Inverse.
	else if (l.inv != nullptr) {
		Matrix ret; 
		ret.rows = l.rows; 
		ret.cols = l.cols;
		ret.Data = *l.inv;
		return ret;
	}

	
    //If not generated;
	int COLS = l.cols;
	int ROWS = l.rows;
	int ACOLS = ROWS;
	int AROWS = ROWS;
	const Matrix r = Matrix::Identity(ROWS);
	//Determinant Preparation;
	int swaps = 0;
	double det = 1;


	//Sort
	std::vector<IVV> sorted;
	for (int i = 0; i < ROWS; ++i) {
		bool insert = false;
		IVV entity; entity.second.first = l[i]; entity.second.second = r[i];
		for (int j = 0; j < COLS; ++j) {
			if (fabs(l[i][j]) > ZERO) {
				entity.first = j;
				for (int k = 0, lk = sorted.size(); k < lk; ++k) {
					if (j < sorted[k].first) {
						sorted.insert(sorted.begin() + k, std::move(entity));
						//Counting swaps;
						swaps += (lk - k) % 2;
						insert = true;
						break;
					}
				}
				if (!insert) {
					sorted.push_back(std::move(entity));
					insert = true;
				}
				break;
			}
			else l[i][j] = 0;
		}
		if (!insert) {
			l.noinv = true;
			l.det = 0;
			NO_INVERSE
		}
	}

    //Elimination && Determinating
	int limit = ROWS;
	for (int r = 0; r < limit; ++r) {

		Vector & rowVec = sorted[r].second.first;
		Vector & ansVec = sorted[r].second.second;
		//Skipping leading zeros
		int c = sorted[r].first;

		//Inverse Error Condition.
		if (c != r || c == COLS) {
			l.noinv = true;
			l.det = 0;
			NO_INVERSE
		}

		//Normalize
		double divident = rowVec[c];
		det *= divident; //det.
		for (int i_c = c; i_c < COLS; ++i_c) {
			rowVec[i_c] /= divident;
		}
		for (int i_c = 0; i_c < ACOLS; ++i_c) {
			ansVec[i_c] /= divident;
		}
		//Eliminate
		for (int i_r = r + 1; i_r < ROWS; ++i_r) {
			Vector & _rowVec = sorted[i_r].second.first;
			Vector & _ansVec = sorted[i_r].second.second;

			double multiplier = _rowVec[c];
			if (fabs(multiplier) < ZERO) {
				_rowVec[c] = 0.0;
				continue;
			}
			bool leadZero = true;
			for (int i_c = c; i_c < COLS; ++i_c) {
				_rowVec[i_c] -= multiplier * rowVec[i_c];
				//Deviation Removal
				if (leadZero && fabs(_rowVec[i_c]) < ZERO) {
					sorted[i_r].first += 1;
					_rowVec[i_c] = 0.0;
				}
				else leadZero = false;
			}
			for (int i_c = 0; i_c < ACOLS; ++i_c) {
				_ansVec[i_c] -= multiplier * ansVec[i_c];
				//Deviation Removal
				if (fabs(_ansVec[i_c]) < ZERO) {
					_ansVec[i_c] = 0.0;
				}
			}
		}

		//Sort
		//OLD Method
		//if (r + 1 != ROWS)	std::qsort(&sorted[r + 1], ROWS - 1 - r, sizeof(IVV), comp_1);

		//Base on the Sqaure and Inverse Criterion Condition.
		//Sorting can be easy and straight forward.
		//NEW Method
		if (r + 1 != ROWS) {
			int _swap = 0;
			int front = r, back = ROWS, pivot = r + 1;
			bool hasreq = false;
			while (1) {
				while (sorted[++front].first == pivot && (hasreq = true) && front + 1 < ROWS);
				while (sorted[--back].first != pivot && back > front);
				if (back <= front) break;
				std::swap(sorted[front], sorted[back]);
				++_swap;
			}
			if (!hasreq) {
				//Error cannot find row with pivot at  r+1;
				l.noinv = true;
				l.det = 0;
				NO_INVERSE
			}
			else {
				swaps += _swap % 2;
			}
		}
	}

	//CleanUp
	for (int i_r = ROWS - 1; i_r >= 0; --i_r) {
		if (sorted[i_r].first == COLS) continue;

		Vector & rowVec = sorted[i_r].second.first;
		Vector & ansVec = sorted[i_r].second.second;
		int leading0 = sorted[i_r].first;

		for (int i_rr = i_r - 1; i_rr >= 0; --i_rr) {
			Vector & _rowVec = sorted[i_rr].second.first;
			Vector & _ansVec = sorted[i_rr].second.second;
			double multiplier = _rowVec[leading0];
			if (fabs(multiplier) < ZERO) {
				_rowVec[leading0] = 0;
				continue;
			}
			for (int i_c = leading0; i_c < COLS; ++i_c) {
				_rowVec[i_c] -= multiplier * rowVec[i_c];
				if (fabs(_rowVec[i_c]) < ZERO) {
					_rowVec[i_c] = 0;
				}
			}
			for (int i_c = 0; i_c < ACOLS; ++i_c) {
				_ansVec[i_c] -= multiplier * ansVec[i_c];
				//Deviation Removal
				if (fabs(_ansVec[i_c]) < ZERO) {
					_ansVec[i_c] = 0;
				}
			}
		}
	}

	
	//Create Result
	Matrix result;
	result.cols = COLS;
	result.rows = ROWS;
	//Save generated inverse
	l.inv = new std::vector<Vector>;
	for (int i = 0; i < ROWS; ++i)
	{
		Vector & trg = sorted[i].second.second;
		result.Data.push_back(trg);
		l.inv->push_back(std::move(trg));
	}
		
	//Save determinant
	l.det = swaps % 2 ? -det : det;
	
	return result;
}

double determ(Matrix &l) {
	if (l.rows != l.cols)CON_ERR
	else if (l.noinv) return 0; //Sqaure but noinverse means no det;
	else if (l.inv != nullptr) {
		//Generated det and inverse.
		return l.det;
	}
	else {
		try
		{
			//Not yet generated det and inverse.
			inverse(l);
		}
		catch (const std::exception& e) {}
		return l.det;
	}
}

std::map<std::string, MatFunc> MatrixOps = {
	{"+",{addm}},
	{"-",{subm}},
	{"*",{multm}},
};