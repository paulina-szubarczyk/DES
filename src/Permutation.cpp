#include "Permutation.h"
#include <iostream>

Permutation::Permutation()
{
}

Permutation::~Permutation() {
	// TODO Auto-generated destructor stub
}

uint64_t Permutation::permutate(uint64_t msg) {

	uint64_t cryptogram = 0;
	for(unsigned i = 0; i<permutation.size(); ++i)
	{
		uint8_t per = 64 - permutation[i];
		uint64_t one = 1;
		uint64_t bit = (msg >> per) & one;
		cryptogram	|= (bit << i);
	}
//	std::cout << "[FINAL] result: " << cryptogram << std::endl;
	return cryptogram;
}


