#include <cstdlib>
#include <stdexcept>
#include "MatrixXnX.h"

template<typename T>
inline int max(const T a, const T b)
{
	return (a > b) * a + (b > a) * b;
}

template<typename T>
inline int min(const T a, const T b)
{
	return (a < b) * a + (b < a) * b;
}

template<typename T>
T MatrixXnX<T>::det(T** arr, uint32_t N)
{
    if (N == 1)
        return arr[0][0];
    if (N == 2)
        return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
    if (N < 1)
        return nan("1");  // Некорректная матрица

    double** subT = new double* [N - 1];  // Субматрица как набор ссылок на исходную матрицу
                                          // Массив ссылок на столбцы субматрицы
    double det__ = 0.;
    int s = 1;                   // Знак минора
    for (int i = 0; i < N; i++)  // Разложение по первому столбцу
    {
        int sub_j = 0;
        for (int j = 0; j < N; j++)         // Заполнение субматрицы ссылками на исходные столбцы
            if (i != j)                     // исключить i строку
                subT[sub_j++] = arr[j] + 1;   // здесь + 1 исключает первый столбец

        det__ = det__ + s * arr[i][0] * det(subT, N - 1);
        s = -s;
    };
    delete[] subT;
    return det__;
};


template<typename T>
T MatrixXnX<T>::CalculateDeterminant() const
{
	

	return T;
}

template<typename T>
T MatrixXnX<T>::CalculateAlgebraicComplement(const uint32_t i, const uint32_t j) const
{

	return T;
}

template<typename T>
T MatrixXnX<T>::element(const uint32_t i, const uint32_t j) const
{
	if (i >= dim || i < 0 || j >= dim || j < 0)
		throw std::range_error("Out of bounds of an array\n");
	return elems[dim * i + j];
}

template<typename T>
void MatrixXnX<T>::setElement(const uint32_t i, const uint32_t j, const T value)
{
	if (i >= dim || i < 0 || j >= dim || j < 0)
		throw std::range_error("Out of bounds of an array\n");
	elems[dim * i + j] = value;
}

template<typename T>
void MatrixXnX<T>::fillRandomElements(const T minVal, const T maxVal)
{
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			elems[dim * i + j] = rand() % (maxVal - minVal + 1) + minVal;
}
