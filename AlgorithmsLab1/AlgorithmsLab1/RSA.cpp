#include "RSA.h"
#include <exception>

RSA::RSA(const BigInt& p, const BigInt& q)
{
	if (!p.IsPrime() || !q.IsPrime())
		throw std::runtime_error("p or q is not prime");
	n = p * q;
	BigInt fi{ (p - 1) * (q - 1) };
	CalculateD(fi);
	CalculateE(d, fi);
}

std::vector<std::string> RSA::Endoce(const std::string& s, const BigInt& e, const BigInt& n)
{
	std::vector<std::string> result;
	auto eCopy = e;
	for (size_t i = 0; i < s.size(); i++)
	{
		BigInt bi((int64_t)s[i]);
		bi = BigInt::Pow(bi, eCopy) % n;
		result.push_back(bi.ToString());
	}

	return result;
}

std::string RSA::Dedoce(const std::vector<std::string>& input)
{
	std::string result;

	for (auto item : input)
	{
		BigInt bi(item);
		bi = BigInt::Pow(bi, d) % n;
		result += (char)bi.ToInt64();
	}

	return result;
}

std::pair<BigInt, BigInt> RSA::GetPublicKey() const
{
	return std::make_pair(e, n);
}

BigInt RSA::CalculateE(BigInt d, BigInt m)
{
	e = 5;
	while (true)
	{
		if ((e * d) % m == 1)
			break;
		else
			++e;
	}
	return e;
}

BigInt RSA::CalculateD(BigInt m)
{
	d = m - 1;
	for (BigInt i = 2; i <= m; i++)
		if ((m % i == 0) && (d % i == 0))
		{
			--d;
			i = 1;
		}
	return d;
}