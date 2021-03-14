#include "RSA.h"
#include <exception>

std::string RSA::ascii;

RSA::RSA(const BigInt& p, const BigInt& q)
{
	if (!p.IsPrime() || !q.IsPrime())
		throw std::runtime_error("p or q is not prime");
	InitASCII();
	n = p * q;
	BigInt fi{ (p - 1) * (q - 1) };
	CalculateD(fi);
	CalculateE(d, fi);
}

std::vector<std::string> RSA::Endoce(const std::string& s, const BigInt& e, const BigInt& n)
{
	InitASCII();
	std::vector<std::string> result;

	for (size_t i = 0; i < s.size(); i++)
	{
		BigInt bi((int64_t)ascii.find(s[i]));
		bi = BigInt::Pow(bi, e.ToInt64()) % n;
		result.push_back(bi.ToString());
	}

	return result;
}

std::string RSA::Dedoce(const std::vector<std::string>& input) const
{
	std::string result;

	for (auto item : input)
	{
		BigInt bi(item);
		bi = BigInt::Pow(bi, d.ToInt64()) % n;
		result += ascii[bi.ToInt64()];
	}

	return result;
}

std::pair<BigInt, BigInt> RSA::GetPublicKey() const
{
	return std::make_pair(e, n);
}

void RSA::InitASCII()
{
	if (ascii.size() == 0)
	{
		for (int i = 0; i <= 127; i++)
			ascii += (char)i;
	}
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