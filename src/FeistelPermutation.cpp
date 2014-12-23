#include "FeistelPermutation.h"
#include <iostream>

FeistelPermutation::FeistelPermutation() :
permutation({16, 7, 20, 21, 29, 12, 28, 17,
			1, 15, 23, 26, 5, 18, 31, 10,
			2, 8, 24, 14, 32, 27, 3, 9,
			19, 13, 30, 6, 22, 11, 4, 25}){}

FeistelPermutation::~FeistelPermutation() {
	// TODO Auto-generated destructor stub
}

void FeistelPermutation::permutate(uint64_t& inout)
{
	uint64_t in = inout;
	inout = 0;

	for(unsigned i = 0; i<permutation.size(); ++i)
	{
		uint8_t per = 32-permutation[i];
		uint64_t one = 1;
		uint64_t bit = (in >> per) & one;
		inout	|= (bit << (31-i));
	}
	std::cout << std::endl;
}
