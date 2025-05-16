#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols) 
	{
		rows = _rows;
		cols = _cols;
		a.resize(rows);
		for (int i = 0; i < rows; i++)
		{
			a[i].resize(cols);
			a[i] = vector<double>(cols, 0);
		}
	}

	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), b.getCols());
		for (int i = 0; i < b.getRows(); i++)
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
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), b.getCols());
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int k = 0; k < b.getCols(); k++)
			{
				for (int n = 0; n < a.getCols(); n++)
				{
					c(i, k) += a(i, n) * b(n, k);
				}
			}
		}
		return c;
	}
	bool operator==(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			return false;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (a(i,j) != b(i,j))
				{
					return false;
				}
			}
		}
		return true;
	}
	bool operator!=(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			return true;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (a(i, j) == b(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}
	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j);
			}
			os << endl;
		}
		return os;
	}
	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) 
	{ 
		(*this)(0, 0) = cos(theta);
		(*this)(0, 1) = -sin(theta);
		(*this)(1, 0) = sin(theta);
		(*this)(1, 1) = cos(theta);
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) 
	{ 
		(*this)(0, 0) = scale;
		(*this)(0, 1) = 0;
		(*this)(1, 0) = 0;
		(*this)(1, 1) = scale;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) 
	{ 
		for (int j = 0; j < nCols; j++)
		{
			(*this)(0, j) = xShift;
			(*this)(1, j) = yShift;
		}

	}
}