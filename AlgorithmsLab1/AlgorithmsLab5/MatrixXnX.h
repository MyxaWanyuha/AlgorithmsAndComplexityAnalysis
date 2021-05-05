#pragma once
#include <ostream>
#include <vector>
class MatrixXnX
{
public:
	MatrixXnX(const uint32_t iDim) : elems(new double[static_cast<uint64_t>(iDim) * iDim]), dim(iDim) {}

	MatrixXnX(const MatrixXnX& m);

	MatrixXnX(MatrixXnX&& m) noexcept;

	~MatrixXnX() { delete[] elems; }

	MatrixXnX& operator=(MatrixXnX&& m) noexcept;

	MatrixXnX& operator=(const MatrixXnX& m);

	double Element(const uint32_t i, const uint32_t j) const;

	void SetElement(const uint32_t i, const uint32_t j, const double value);

	uint32_t GetDim() const noexcept { return dim; }

	MatrixXnX GetMatrixWithoutStrCol(uint32_t str, uint32_t col) const;

	double Determinant() const;

	MatrixXnX InverseMatrix() const;

	void Transpose();

	std::vector<double> operator*(const std::vector<double>& v) const;
private:
	double* elems = nullptr;
	uint32_t dim = 0;
	void Copy(const MatrixXnX& src);
};

std::ostream& operator<<(std::ostream& os, const MatrixXnX& m);

bool operator==(const MatrixXnX& m1, const MatrixXnX& m2);