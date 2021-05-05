#include <stdexcept>
#include "MatrixXnX.h"

MatrixXnX::MatrixXnX(const MatrixXnX& m) : MatrixXnX(m.dim)
{
	Copy(m);
}

MatrixXnX::MatrixXnX(MatrixXnX&& m) noexcept
	: elems(m.elems), dim(m.dim)
{
	m.elems = nullptr;
}

MatrixXnX& MatrixXnX::operator=(MatrixXnX&& m) noexcept
{
	delete[] elems;
	elems = m.elems;
	dim = m.dim;
	m.elems = nullptr;
	return *this;
}

MatrixXnX& MatrixXnX::operator=(const MatrixXnX& m)
{
	delete[] elems;
	dim = m.dim;
	Copy(m);
	return *this;
}

double MatrixXnX::Element(const uint32_t i, const uint32_t j) const
{
	if (i >= dim || i < 0 || j >= dim || j < 0)
		throw std::range_error("Out of bounds of an array\n");
	return elems[dim * i + j];
}

void MatrixXnX::SetElement(const uint32_t i, const uint32_t j, const double value)
{
	if (i >= dim || i < 0 || j >= dim || j < 0)
		throw std::range_error("Out of bounds of an array\n");
	elems[dim * i + j] = value;
}

MatrixXnX MatrixXnX::GetMatrixWithoutStrCol(uint32_t str, uint32_t col) const
{
	MatrixXnX submatrix(GetDim() - 1);
	uint32_t subi = 0;
	for (uint32_t i = 0; i < GetDim(); i++)
	{
		uint32_t subj = 0;
		if (i == str) continue;

		for (uint32_t j = 0; j < GetDim(); j++)
		{
			if (j == col) continue;
			submatrix.SetElement(subi, subj, Element(i, j));
			subj++;
		}
		subi++;
	}
	return submatrix;
}

double MatrixXnX::Determinant() const
{
	if (GetDim() == 1)
		return Element(0, 0);

	if (GetDim() == 2)
		return Element(0, 0) * Element(1, 1) - Element(1, 0) * Element(0, 1);

	double result = 0.0;
	int8_t signMultiplier = 1;
	for (uint32_t i = 0; i < GetDim(); i++)
	{
		auto p = GetMatrixWithoutStrCol(0, i);
		result += signMultiplier * Element(0, i) * p.Determinant();
		signMultiplier *= -1;
	}
	return result;
}

MatrixXnX MatrixXnX::InverseMatrix() const
{
	auto determinant = Determinant();
	if (determinant == 0) return MatrixXnX(0);

	MatrixXnX result(GetDim());

	for(uint32_t i = 0; i < GetDim(); ++i)
		for (uint32_t j = 0; j < GetDim(); ++j)
		{
			int8_t sign = (i + j + 2) % 2 ? -1 : 1;
			result.SetElement(i, j, sign * GetMatrixWithoutStrCol(i, j).Determinant() / determinant);
		}
	result.Transpose();
	return result;
}

void MatrixXnX::Transpose()
{
	for (uint32_t i = 0; i < GetDim(); ++i)
		for (uint32_t j = i + 1; j < GetDim(); ++j)
		{
			auto e1 = Element(i, j);
			SetElement(i, j, Element(j, i));
			SetElement(j, i, e1);
		}
}

void MatrixXnX::Copy(const MatrixXnX& src)
{
	for (uint32_t i = 0; i < dim; i++)
		for (uint32_t j = 0; j < dim; j++)
			SetElement(i, j, src.Element(i, j));
}

std::ostream& operator<<(std::ostream& os, const MatrixXnX& m)
{
	for (uint32_t i = 0; i < m.GetDim(); i++)
	{
		for (uint32_t j = 0; j < m.GetDim(); j++)
			os << m.Element(i, j) << '\t';
		os << '\n';
	}
	return os;
}