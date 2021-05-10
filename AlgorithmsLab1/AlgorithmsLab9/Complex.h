#pragma once
class Complex
{
public:
	Complex() {};
	Complex(double real, double imag = 0.0) :real(real), imag(imag) {}

	double Real() const { return real; }
	double Imag() const { return imag; }

private:
	double real = 0.0;
	double imag = 0.0;
};

Complex operator+(const Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
Complex operator/(const Complex& a, const Complex& b);
