#pragma once
#include <vector>
#include <cmath>
class Polynomial
{
public:
	Polynomial(const std::vector<double>& multipliers) : multipliers(multipliers) {};
	double ValueAtPoint(double x) const
	{
		double res = multipliers[0];
		for (int i = 1; i < multipliers.size(); ++i)
			res += multipliers[i] * std::pow(x, i);
		return res;
	}

private:
	std::vector<double> multipliers;
};
