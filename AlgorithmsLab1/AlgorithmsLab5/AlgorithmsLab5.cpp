#include <iostream>
#include "MatrixXnX.h"


int main()
{
    std::cout << "Enter the dimension of the quadratic system of equations: ";
    uint32_t dim;
    std::cin >> dim;
    if (dim == 0) return 0;
    MatrixXnX matr(dim);
    std::vector<double> freeMembers(dim);

    for(uint32_t i = 0; i < dim; ++i)
    {
        double e;
        std::cout << "equation " << i << ":\n";
        for (uint32_t j = 0; j < dim; ++j)
        {
            std::cout << 'x' << j << " = ";
            std::cin >> e;
            matr.SetElement(i, j, e);
        }
        std::cout << "free member " << i << " = ";
        std::cin >> e;
        freeMembers[i] = e;
    }
    std::cout << '\n';

    auto invMatr = matr.InverseMatrix();
    if (invMatr.GetDim() == 0)
    {
        std::cout << "no solutions\n";
        return 1;
    }

    auto vectorUnknowns = invMatr * freeMembers;
    for(uint32_t i = 0; i < vectorUnknowns.size(); i++)
        std::cout << 'x' << i << " = " << vectorUnknowns[i] << '\n';
    return 0;
}

/*
1. Написать функцию вычисления определителя квадратной матрицы, раскрывая определитель по строке.

2. Написать функцию вычисления обратной матрицы, с использованием алгебраических дополнений.

3. Написать функцию умножения матрицы на вектор.

4. Решить квадратную систему линейных уравнений методом обратной матрицы.

Функция выдает ответы :

– решение в случае его единственности;

– нет решений или решений бесконечно много.

5. Определить сложность алгоритма.
*/
