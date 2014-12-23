#include "DES.h"
#include <iostream>
#include "utils.h"

DES::DES(uint64_t key):  k(key),g(k) {}

uint64_t DES::shift(uint64_t L, uint64_t R)
{
	std::cout << "R: " << R << "\t" ;
	std::cout << "L: " << L << "\n" ;

	return (R << 32) | L ;
}

void DES::round(uint8_t i, uint64_t& c)
{
	uint64_t key = g.generateKey(i);

	std::cout << "key: " << key << "\t" ;

	uint64_t Ri = utils::right_half(c);

//	std::cout << "R0: " << Ri << "\t" ;

	uint64_t Rn = f.calculate(Ri,key);

	uint64_t R = utils::left_half(c) ^ Rn;

	c = (Ri << 32) | R ;
}

uint64_t DES::encrypt(uint64_t m)
{

	uint64_t c = 0;

	c = ip.permutate(m);

	utils::print_uint64(c);

	for(int i=0; i<16; ++i)

	{
		std::cout << "ROUND i: " << i << "\t";

		round((int8_t)i,c);

		utils::print_uint64(c);
	}

	c = shift(utils::left_half(c),utils::right_half(c));

	utils::print_uint64(c);

	c = ip_1.permutate(c);

	utils::print_uint64(c);

	std::cout << "END\n";

	return c;
}

uint64_t DES::decrypt(uint64_t c)
{
	uint64_t m = 0;

	m = ip.permutate(c);

	utils::print_uint64(m);

	for(int i=15; i>=0; --i)
	{
		std::cout << "ROUND i: " << i << "\t";

		round((int8_t)i,m);

		utils::print_uint64(m);
	}

	m = shift(utils::left_half(m),utils::right_half(m));

	utils::print_uint64(m);

	m = ip_1.permutate(m);

	utils::print_uint64(m);

	return m;
}

