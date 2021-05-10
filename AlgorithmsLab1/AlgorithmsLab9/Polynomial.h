#pragma once
#include <vector>
class Polynomial
{
public:
	Polynomial(const std::vector<double>& multipliers) : multipliers(multipliers) {};
	Polynomial(size_t multipliersCount) : multipliers(multipliersCount) {};
	size_t Length() const { return multipliers.size(); }
	const double& operator[](std::size_t position) const
	{
		return multipliers[position];
	}
	double& operator[](std::size_t position)
	{
		return const_cast<double&>(static_cast<const Polynomial&>(*this)[position]);
	}


	friend Polynomial operator+(const Polynomial& a, const Polynomial& b);
	friend Polynomial operator-(const Polynomial& a, const Polynomial& b);
	friend Polynomial operator*(const Polynomial& a, const Polynomial& b);
	friend Polynomial operator/(const Polynomial& a, const Polynomial& b);

private:
	std::vector<double> multipliers;
};

