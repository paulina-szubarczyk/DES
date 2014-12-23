#include "ExpansionFunction.h"
#include <iostream>

ExpansionFunction::ExpansionFunction() :
permutation({32, 1, 2, 3, 4, 5,
			4, 5, 6, 7, 8, 9,
			8, 9, 10, 11, 12, 13,
			12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21,
			20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29,
			28, 29, 30, 31, 32, 1})
{}

ExpansionFunction::~ExpansionFunction()
{}

void ExpansionFunction::expand(uint64_t& inout)
{
	uint64_t in = inout;
	inout = 0;

	for(unsigned i = 0; i<permutation.size(); ++i)
	{
		uint8_t per = permutation[i]-1;
		uint64_t one = 1;
		uint64_t bit = (in >> per) & one;
		inout	|= (bit << i);
	}
//	std::cout << "\nresult: " << inout << std::endl;
}
