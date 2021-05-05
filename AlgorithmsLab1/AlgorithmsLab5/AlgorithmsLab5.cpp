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
        double input;
        std::cout << "equation " << i << ":\n";
        for (uint32_t j = 0; j < dim; ++j)
        {
            std::cout << 'x' << j << " = ";
            std::cin >> input;
            matr.SetElement(i, j, input);
        }
        std::cout << "free member " << i << " = ";
        std::cin >> input;
        freeMembers[i] = input;
    }
    std::cout << '\n';

    auto invMatr = matr.InverseMatrix();
    if (invMatr.GetDim() == 0)
    {
        std::cout << "no solutions\n";
        return 0;
    }

    auto vectorUnknowns = invMatr * freeMembers;
    for(uint32_t i = 0; i < vectorUnknowns.size(); i++)
        std::cout << 'x' << i << " = " << vectorUnknowns[i] << '\n';
    return 0;
}
