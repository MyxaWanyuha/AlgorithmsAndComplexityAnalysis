#pragma once
#include <vector>
#include <string>
#include "BigInt.h"

class RSA
{
public:
	explicit RSA(const BigInt& p, const BigInt& q);
	static std::vector<std::string> Endoce(const std::string& s, const BigInt& e, const BigInt& n);
	std::string Dedoce(const std::vector<std::string>& input);
	std::pair<BigInt, BigInt> GetPublicKey() const;
private:
	BigInt n;
	BigInt d;
	BigInt e;
	BigInt CalculateE(BigInt d, BigInt m);
	BigInt CalculateD(BigInt m);
};