#include <iostream>
#include <functional>
#include "Polynomial.h"

double RightRectangleIntegral(const std::function<double(double)>& f, double leftBorder, double rightBorder, uint64_t stepCount)
{
    auto step = (rightBorder - leftBorder) / stepCount;
    auto sum = 0.0;
    for (int i = 1; i <= stepCount; i++)
        sum += f(leftBorder + i * step);
    return step * sum;
}

double CentralRectangleIntegral(const std::function<double(double)>& f, double leftBorder, double rightBorder, uint64_t stepCount)
{
    auto step = (rightBorder - leftBorder) / stepCount;
    auto sum = (f(leftBorder) + f(rightBorder)) * 0.5;
    for (int i = 1; i < stepCount; i++)
        sum += f(leftBorder + step * i);
    return step * sum;
}

double TrapeziumIntegral(const std::function<double(double)>& f, double leftBorder, double rightBorder, uint64_t stepCount)
{
    const double width = (rightBorder - leftBorder) / stepCount;
    double sum = 0;
    for (uint64_t step = 0; step < stepCount; step++)
    {
        const double x1 = leftBorder + step * width;
        const double x2 = leftBorder + (step + 1) * width;
        sum += 0.5 * (x2 - x1) * (f(x1) + f(x2));
    }
    return sum;
}

double SimpsonIntegral(const std::function<double(double)>& f, double leftBorder, double rightBorder, uint64_t stepCount)
{
    auto h = (rightBorder - leftBorder) / stepCount;
    auto sum1 = 0.;
    auto sum2 = 0.;
    for (int64_t step = 1; step <= stepCount; step++)
    {
        auto xk1 = leftBorder + step * h;
        if (step <= stepCount - 1)
            sum1 += f(xk1);
        auto xk2 = leftBorder + (step - 1) * h;
        sum2 += f(0.5 * (xk1 + xk2));
    }
    return h / 3. * (0.5 * f(leftBorder) + sum1 + 2. * sum2 + 0.5 * f(rightBorder));
}

double GaussIntegral(const std::function<double(double)>& f, double leftBorder, double rightBorder, uint64_t stepCount)
{
    auto s = 0.;
    auto h = (rightBorder - leftBorder) / stepCount;
    auto x12 = leftBorder + h * 0.5;
    auto x1 = x12 - h * 0.5;
    auto x2 = x12 + h * 0.5;
    for (int i = 1; i <= stepCount; i++)
    {
        s += f(x1) + f(x2);
        x12 += h;
        x1 = x12 - h * 0.5;
        x2 = x12 + h * 0.5;
    }
    return h * 0.5 * s;
}

double ChebyshevIntegral(const std::function<double(double)>& f, double leftBorder, double rightBorder, uint64_t stepCount)
{
    double s = 0;
    auto h = (rightBorder - leftBorder) / stepCount;
    for (int i = 0; i < stepCount; ++i)
    {
        double a1 = leftBorder + h * i;
        double b1 = a1 + h;
        s += ((b1 - a1) * 0.5) * (f((a1 + b1) * 0.5 - ((b1 - a1) * 0.5))
                                + f((a1 + b1) * 0.5 + ((b1 - a1) * 0.5)));
    }
    return s;
}

void TestIntegrals(std::function<double(double)>& f, double firstBorder, double secondBorder, const uint32_t& n)
{
    std::cout << "CentralRectangleIntegral:\t" << CentralRectangleIntegral(f, firstBorder, secondBorder, n) << '\n';
    std::cout << "RightRectangleIntegral:\t\t" << RightRectangleIntegral(f, firstBorder, secondBorder, n) << '\n';
    std::cout << "TrapeziumIntegral:\t\t" << TrapeziumIntegral(f, firstBorder, secondBorder, n) << '\n';
    std::cout << "SimpsonIntegral:\t\t" << SimpsonIntegral(f, firstBorder, secondBorder, n) << '\n';
    std::cout << "GaussIntegral:\t\t\t" << GaussIntegral(f, firstBorder, secondBorder, n) << '\n';
    std::cout << "ChebyshevIntegral:\t\t" << ChebyshevIntegral(f, firstBorder, secondBorder, n) << '\n';
}

int main()
{
    std::cout << "Enter the highest degree of the polynomial: ";
    int maxDegree = 0;
    std::cin >> maxDegree;
    
    std::cout << "Polynomial: A[0] + A[1]*X^1 + ... + A[n]*X^n \n";
    std::vector<double> v;
    for (int i = 0; i <= maxDegree; ++i)
    {
        std::cout << "A[" << i << "] = ";
        double newNum = 0.;
        std::cin >> newNum;
        v.push_back(newNum);
    }

    double firstBorder;
    double secondBorder;
    uint32_t n;

    std::cout << "Enter the first border: ";
    std::cin >> firstBorder;
    std::cout << "Enter the second border: ";
    std::cin >> secondBorder;

    if (firstBorder > secondBorder)
        std::swap(firstBorder, secondBorder);

    std::cout << "Enter the number of line splits: ";
    std::cin >> n;

    Polynomial p(v);
    std::function<double(double)> f = std::bind1st(std::mem_fun(&Polynomial::ValueAtPoint), &p);
    TestIntegrals(f, firstBorder, secondBorder, n);

    f = [](double x) { return std::cos(x); };
    std::cout << "cos:\n";
    TestIntegrals(f, firstBorder, secondBorder, n);

    f = [](double x) { return std::sin(x); };
    std::cout << "sin:\n";
    TestIntegrals(f, firstBorder, secondBorder, n);

    f = [](double x) { return std::tan(x); };
    std::cout << "tan:\n";
    TestIntegrals(f, firstBorder, secondBorder, n);

    return 0;
}
