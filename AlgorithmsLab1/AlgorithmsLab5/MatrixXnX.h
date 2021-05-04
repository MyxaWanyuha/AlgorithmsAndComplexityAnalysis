#pragma once
#include <ostream>
#include <cstdlib>
#include <stdexcept>

template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
class MatrixXnX
{
public:
	MatrixXnX(const uint32_t iDim) : elems(new T[static_cast<uint64_t>(iDim) * iDim]), dim(iDim) {};

	MatrixXnX(const MatrixXnX& m) : MatrixXnX(m.dim)
	{
		for (uint32_t i = 0; i < dim; i++)
			for (uint32_t j = 0; j < dim; j++)
				SetElement(i, j, m.element(i, j));
	}

	MatrixXnX(MatrixXnX&& m) noexcept : MatrixXnX(m.dim)
	{
		for (uint32_t i = 0; i < dim; i++)
			for (uint32_t j = 0; j < dim; j++)
				SetElement(i, j, m.element(i, j));
	}

	~MatrixXnX() { delete[] elems; }

	MatrixXnX& operator=(MatrixXnX&& m)
	{
		delete[] elems;
		elems = m.elems;
		dim = m.dim;
	}

	MatrixXnX& operator=(const MatrixXnX& m)
	{
		delete[] elems;
		dim = m.dim;		
		for (uint32_t i = 0; i < dim; i++)
			for (uint32_t j = 0; j < dim; j++)
				SetElement(i, j, m.element(i, j));
	}

	T element(const uint32_t i, const uint32_t j) const
	{
		if (i >= dim || i < 0 || j >= dim || j < 0)
			throw std::range_error("Out of bounds of an array\n");
		return elems[dim * i + j];
	}

	void SetElement(const uint32_t i, const uint32_t j, const T value)
	{
		if (i >= dim || i < 0 || j >= dim || j < 0)
			throw std::range_error("Out of bounds of an array\n");
		elems[dim * i + j] = value;
	}

	uint32_t GetDim() const noexcept { return dim; }

	MatrixXnX<T> GetMatrixWithout_xStr_yCol(MatrixXnX<T>& matrix, uint32_t x, uint32_t y)
	{
		MatrixXnX<T> submatrix(matrix.GetDim() - 1);
		uint32_t subi = 0;
		for (uint32_t i = 0; i < matrix.GetDim(); i++)
		{
			uint32_t subj = 0;
			if (i == y) continue;

			for (uint32_t j = 0; j < matrix.GetDim(); j++)
			{
				if (j == x) continue;
				submatrix.SetElement(subi, subj, matrix.element(i, j));
				subj++;
			}
			subi++;
		}
		return submatrix;
	}

	T Determinant()
	{
		if (GetDim() == 1)
			return element(0, 0);

		if (GetDim() == 2)
			return element(0, 0) * element(1, 1) - element(1, 0) * element(0, 1);

		T result = 0;
		int8_t signMultiplier = 1;
		for (uint32_t i = 0; i < GetDim(); i++)
		{
			auto p = GetMatrixWithout_xStr_yCol(*this, i, 0);
			result += signMultiplier * element(0, i) * p.Determinant();
			signMultiplier *= -1;
		}
		return result;
	}

private:
	T* elems;
	uint32_t dim;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const MatrixXnX<T>& m)
{
	for (uint32_t i = 0; i < m.GetDim(); i++)
	{
		for (uint32_t j = 0; j < m.GetDim(); j++)
			os << m.element(i, j) << ' ';
		os << '\n';
	}
	return os;
}