#include <exception>
#include "Complex.h"

Complex operator+(const Complex& a, const Complex& b)
{
	return Complex(a.Real() + b.Real(), a.Imag() + b.Imag());
}

Complex operator-(const Complex& a, const Complex& b)
{
	return Complex(a.Real() - b.Real(), a.Imag() - b.Imag());
}

Complex operator*(const Complex& a, const Complex& b)
{
	return Complex(a.Real() * b.Real() - a.Imag() * b.Imag(), a.Imag() * b.Real() + a.Real() * b.Imag());
}

Complex operator/(const Complex& a, const Complex& b)
{
	if (b.Real() == 0.0 && b.Imag() == 0.0)
		throw std::exception("Divide by zero");
	auto denominator = (b.Real() * b.Real() + b.Imag() * b.Imag());
	auto real = (a.Real() * b.Real() + a.Imag() * b.Imag()) / denominator;
	auto imag = (a.Imag() * b.Real() - a.Real() * b.Imag()) / denominator;
	return Complex(real, imag);
}
