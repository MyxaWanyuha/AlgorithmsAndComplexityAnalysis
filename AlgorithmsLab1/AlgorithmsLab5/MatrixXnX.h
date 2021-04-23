#pragma once

template<typename T>
class MatrixXnX
{
public:
	MatrixXnX(const uint32_t iDim) : elems(new T[iDim * iDim]), dim(iDim) {};
	~MatrixXnX() { delete[] elems; }
	MatrixXnX(const MatrixXnX&) = delete;
	MatrixXnX& operator=(const MatrixXnX&) = delete;
	MatrixXnX(MatrixXnX&&) = delete;
	MatrixXnX& operator=(MatrixXnX&&) = delete;

	T CalculateDeterminant() const;
	T CalculateAlgebraicComplement(const uint32_t i, const uint32_t j) const;
	T det(T** arr, uint32_t N);
	T element(const uint32_t i, const uint32_t j) const;
	void setElement(const uint32_t i, const uint32_t j, const T value);
	void fillRandomElements(const T minVal, const T maxVal);
	uint32_t GetDim() const { return dim; };
private:
	T* elems;
	uint32_t dim;
};


