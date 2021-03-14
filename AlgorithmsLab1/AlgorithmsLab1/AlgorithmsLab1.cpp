#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "BigInt.h"
#include "RSA.h"

void test()
{
	std::string error = "Error #";
	uint32_t errorNum = 0;
	// x + y
	{
		errorNum++;
		BigInt x(12345);
		BigInt y(23);
		BigInt ans(12368);
		BigInt res;
		res = x + y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x + (-y)
	{
		errorNum++;
		BigInt x(12345);
		BigInt y(-23);
		BigInt ans(12322);  // 12322
		BigInt res;
		res = x + y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x - y
	{
		errorNum++;
		BigInt x(12345);
		BigInt y(23);
		BigInt ans(12322);  // x - y = 12322
		BigInt res;
		res = x - y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// -x - -y
	{
		errorNum++;
		BigInt x(-12345);
		BigInt y(-23);
		BigInt ans(-12322);  // -x - -y = -12322
		BigInt res;
		res = x - y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x + (-y) = -res
	{
		errorNum++;
		BigInt x(45);
		BigInt y(-100);
		BigInt ans(-55);  // x + y = -55
		BigInt res;
		res = x + y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x + y + x - y - x
	{
		errorNum++;
		BigInt x(45);
		BigInt y(-100);
		BigInt res;
		res = x + y + x - y - x;
		if (res != x)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x * 2
	{
		errorNum++;
		BigInt x(45);
		BigInt ans(90);
		BigInt res;
		res = x * 2;  //45*2=90
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x * 2
	{
		errorNum++;
		BigInt x(45);
		BigInt ans(90);
		BigInt res;
		res = x * 2;  //45*2=90
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// 2 * x * 10
	{
		errorNum++;
		BigInt x(45);
		BigInt ans(900);
		BigInt res;
		res = 2 * x * 10;

		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x * 10^4
	{
		errorNum++;
		BigInt x(45);
		BigInt ans(450000);
		BigInt res;
		res = x * static_cast<int64_t>(std::pow(10, 4));  // 45*10^4

		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x * y
	{
		errorNum++;
		BigInt x(12);
		BigInt y(4);
		BigInt ans(48);
		BigInt res;
		res = x * y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// a * (b + c) == a * b + a * c
	{
		errorNum++;
		BigInt a(123456789);
		BigInt b("435321234543212343217");
		BigInt c(42132);
		BigInt arg1;
		arg1 = b + c;
		arg1 = a * arg1;
		BigInt arg2;
		arg2 = a * b;
		arg2 = a * c + arg2;
		if (arg1 != arg2)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	{
		errorNum++;
		BigInt a(12);
		BigInt b(4);
		BigInt c(32);
		BigInt arg1, buf;
		buf = (b + c);
		arg1 = a * buf;
		BigInt arg2;
		arg2 = a * b;
		arg2 = a * c + arg2;
		if (arg1 != arg2)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	{
		errorNum++;
		BigInt a(123212321231);
		BigInt b("4222222222422222222242222222224222222222");
		BigInt c(32);
		BigInt arg1, buf;
		buf = (b + c);
		arg1 = a * buf;
		BigInt arg2;
		arg2 = a * b;
		arg2 = a * c + arg2;
		if (arg1 != arg2)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x + (-x) = 0
	{
		errorNum++;
		BigInt x("7656576567567");
		BigInt y("-7656576567567");
		BigInt ans; // 0
		BigInt res;
		res = x + y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// a / -a = -1
	{
		errorNum++;
		BigInt x("7656576567567");
		BigInt y("-7656576567567");
		BigInt ans(-1);
		BigInt res;
		res = x / y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x / 2
	{
		errorNum++;
		BigInt x(44);
		BigInt ans(22);
		BigInt res;
		res = x / 2;  //45*2=90
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// 22 / x
	{
		errorNum++;
		BigInt x(11);
		BigInt ans(2);
		BigInt res;
		res = 22 / x;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x / 10^4
	{
		errorNum++;
		BigInt x(45);
		BigInt ans;//0
		BigInt res;
		res = x / static_cast<int64_t>(std::pow(10, 4));  // 45*10^4

		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x / y
	{
		errorNum++;
		BigInt x(12);
		BigInt y(4);
		BigInt ans(3);
		BigInt res;
		res = x / y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x % 2 = 0
	{
		errorNum++;
		BigInt x(44);
		BigInt ans(0);
		BigInt res;
		res = x % 2;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x % 2 = 1
	{
		errorNum++;
		BigInt x(43);
		BigInt ans(1);
		BigInt res;
		res = x % 2;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// 22 % x
	{
		errorNum++;
		BigInt x(3);
		BigInt ans(1);
		BigInt res;
		res = 22 % x;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x / y
	{
		errorNum++;
		BigInt x(13);
		BigInt y(4);
		BigInt ans(1);
		BigInt res;
		res = x % y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// x / y
	{
		errorNum++;
		BigInt x(13);
		BigInt y(4);
		BigInt ans(1);
		BigInt res;
		res = x % y;
		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// ++x x++
	{
		errorNum++;
		BigInt x(13);
		BigInt ans(14);
		BigInt res;
		res = ++x; //x = 14

		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';
		
		errorNum++;
		res = x++;
		ans = 14;
		if (res != ans && x == 15)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// --x x--
	{
		errorNum++;
		BigInt x(13);
		BigInt ans(12);
		BigInt res;
		res = --x; //x = 12

		if (res != ans)
			std::cout << error + std::to_string(errorNum) << '\n';

		errorNum++;
		res = x--;
		if (res != ans && x == 11)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// operator<
	{
		errorNum++;
		BigInt x(13);
		BigInt y(4);
		if (!(y < x))
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// operator>
	{
		errorNum++;
		BigInt x(13);
		BigInt y(4);
		if (!(x > y))
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// operator<=
	{
		errorNum++;
		BigInt x(13);
		BigInt y(13);
		if (!(y <= x))
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// operator>=
	{
		errorNum++;
		BigInt x(4);
		BigInt y(4);
		if (!(x >= y))
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// operator==
	{
		errorNum++;
		BigInt x(4);
		BigInt y(4);
		if (!(y == x))
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// operator!=
	{
		errorNum++;
		BigInt x(13);
		BigInt y(-4);
		if (!(y != x))
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	//static BigInt Pow(const BigInt& base, int64_t exp);
	{
		errorNum++;
		BigInt x(11);
		x = BigInt::Pow(x, 2);
		if (x != 121)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	//bool IsPrime() const;
	{
		errorNum++;
		BigInt x(13);
		BigInt y(-4);
		if (!x.IsPrime() && y.IsPrime())
			std::cout << error + std::to_string(errorNum) << '\n';
	}
	// RSA
	{
		RSA rsa(19, 23);
		std::string mes;
		for (int i = 0; i <= 127; i++)
			mes += static_cast<char>(i);
		auto res = rsa.Endoce(mes, rsa.GetPublicKey().first, rsa.GetPublicKey().second);
		auto dec = rsa.Dedoce(res);
		if(mes != dec)
			std::cout << error + std::to_string(errorNum) << '\n';
	}
}

int main()
{
	test();
	std::string PublicKeyFileName = "PublicKey.txt";
	std::string MessageFileName = "message.txt";
	std::string EncodeMessageFileName = "EncodeMessage.txt";
	std::string DecodeMessageFileName = "DecodeMessage.txt";

	RSA John_rsa(19, 23);
	// John
	{
		std::ofstream John_ofs_PublicKey(PublicKeyFileName);
		John_ofs_PublicKey << John_rsa.GetPublicKey().first << " " << John_rsa.GetPublicKey().second;
	}
	// Mary
	{
		std::ifstream Mary_ifs_PublicKey(PublicKeyFileName);
		BigInt e, n;
		if (Mary_ifs_PublicKey.is_open())
		{
			std::string line;
			std::getline(Mary_ifs_PublicKey, line);
			std::istringstream iss(line);
			if (!(iss >> e >> n))
				throw std::runtime_error("can't read public key");
		}
		else
			throw std::runtime_error(PublicKeyFileName + " not found");

		std::string message;
		std::ifstream Mary_ifs_Message(MessageFileName);
		if (Mary_ifs_Message.is_open())
			message.assign((std::istreambuf_iterator<char>(Mary_ifs_Message)), (std::istreambuf_iterator<char>()));
		else
			throw std::runtime_error(MessageFileName + " not found");

		auto encodeText = RSA::Endoce(message, e, n);
		std::ofstream Mary_of(EncodeMessageFileName);
		for (auto& str : encodeText)
			Mary_of << str << '\n';
	}
	// John
	{
		std::ifstream John_if(EncodeMessageFileName);
		std::vector<std::string> encodeText;
		if (John_if.is_open())
		{
			std::string line;
			while (std::getline(John_if, line))
				encodeText.push_back(line);
		}
		else
			throw std::runtime_error(EncodeMessageFileName + " not found");

		auto dencodeText = John_rsa.Dedoce(encodeText);
		std::ofstream John_of(DecodeMessageFileName);
		John_of << dencodeText;
	}
	return 0;
}
