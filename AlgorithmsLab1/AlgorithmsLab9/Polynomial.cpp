#include "Polynomial.h"

Polynomial operator+(const Polynomial& a, const Polynomial& b)
{
	auto& changedPolynomial = const_cast<Polynomial&>(b);
	if(a.Length() > b.Length())
	{
		auto dif = a.Length() - b.Length();
		for (uint32_t i = 0; i < dif; ++i)
			changedPolynomial.multipliers.push_back(0.0);
	}
	else
	{
		changedPolynomial = const_cast<Polynomial&>(a);
		auto dif = b.Length() - a.Length();
		for (uint32_t i = 0; i < dif; ++i)
			changedPolynomial.multipliers.push_back(0.0);
	}

	Polynomial result(a.Length());
	for (uint32_t i = 0; i < a.Length(); ++i)
		result[i] = a[i] + b[i];

	for (size_t i = changedPolynomial.Length(); i > 0; --i)
		if (changedPolynomial.multipliers[i] == 0)
			changedPolynomial.multipliers.pop_back();
		else return result;

	return result;
}
