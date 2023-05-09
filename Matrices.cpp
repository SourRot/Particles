#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;

		a.resize(rows, vector<double>(cols, 0));
		/*THIS CODE BELOW DOES THE SAME AS THIS LINE ^
		//resize our 2D vector a
		//a's type: vector<vector<double>> a
		a.resize(rows);
		for (size_t i = 0; i < a.size(); i++)
		{
			//a[i].resize(cols);
			a.at(i).resize(cols);
			//while we are in here we can intialize each column
			for (size_t j = 0; j < cols; j++)
			{
				//a[i][j] = 0;
				a.at(i).at(j) = 0;
			}
		}*/
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << " ";
			}
			os << endl;
		}
		return os; //allows chaining statements eg cout << a << endl;
	}

	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), a.getCols());
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		/*a(i, j) can only be multiplied by b if b's rows matches a's columns so b(j, k)
		Pseudocode:
		initialize c(i, k)
		for(i...)
		{
			for(k...)
			{
				for(j...)
				{
					c(i,k) += a(i,j) * b(j, k)
				}
			}
		}*/

		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), b.getCols());	//initializes each cell to 0 (our constructor is coded that way)
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int k = 0; k < b.getCols(); k++)
			{
				for (int j = 0; j < a.getCols(); j++)
				{
					c(i, k) += a(i, j) * b(j, k);
				}
			}
		}
		return c;
	}

	bool operator==(const Matrix& a, const Matrix& b)
	{
		bool matching = true;
		if (a.getCols() == b.getCols() && a.getRows() == b.getRows())
		{
			for (int i = 0; i < a.getRows() && matching; i++)
			{
				for (int j = 0; j < a.getCols() && matching; j++)
				{
					if (fabs(a(i, j) - b(i, j)) < 0.001)
					{
						matching = true;
					}
					else
					{
						matching = false;
					}
				}
			}
		}
		else { matching = false; }

		return matching;
	}

	bool operator!=(const Matrix& a, const Matrix& b)
	{
		bool notMatching = false;
		if (a.getCols() == b.getCols() && a.getRows() == b.getRows())
		{
			for (int i = 0; i < a.getRows() && !notMatching; i++)
			{
				for (int j = 0; j < a.getCols() && !notMatching; j++)
				{
					if (fabs(a(i, j) - b(i, j)) > 0.001)
					{
						notMatching = true;
					}
					else
					{
						notMatching = false;
					}
				}
			}
		}
		else { notMatching = true; }

		return notMatching;
	}
	RotationMatrix::RotationMatrix(double theta) : Matrix(2,2)
	{
		a[0][0] = cos(theta);
		a[0][1] = -sin(theta);
		a[1][0] = sin(theta);
		a[1][1] = cos(theta);
	}
	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
		(*this)(0, 0) = scale;
		(*this)(1, 1) = scale;
	}
	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols + 1)
	{
			for (int j = 0; j < nCols; j++)
			{
				a[0][j] = xShift;
				a[1][j] = yShift;
			}
		
	}
}
