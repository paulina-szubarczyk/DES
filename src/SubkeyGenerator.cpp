#include "SubkeyGenerator.h"


SubkeyGenerator::SubkeyGenerator(uint64_t key)
: ps2({14,17,11,24,1,5,3,28,
	15,6,21,10,23,19,12,4,
	26,8,16,7,27,20,13,2,
	41,52,31,37,47,55,30,40,
	51,45,33,48,44,49,39,56,
	34,53,46,42,50,36,29,32})
{
	std::vector<uint8_t> ps1_C({57,49,41,33,25,17,9,
								1,58,50,42,34,26,18,
								10,2,59,51,43,35,27,
								19,11,3,60,52,44,36});

	std::vector<uint8_t> ps1_D({63,55,47,39,31,23,15,
								7,62,54,46,38,30,22,
								14,6,61,53,45,37,29,
								21,13,5,28,20,12,4});

	C = generate_half(key, ps1_C);
	D = generate_half(key, ps1_D);
}

SubkeyGenerator::~SubkeyGenerator() {}

uint64_t SubkeyGenerator::generateKey(uint8_t i)
{
	uint64_t mask = (1 << 29) - 1;
	uint64_t L = (C << i) | (C >> (28-i));
	uint64_t R = (D >> i) | (D << (28-i));
	uint64_t key = ((L & mask) << 28) | (R & mask);

	permutate(key);

	return key;
}

uint64_t SubkeyGenerator::generate_half(uint64_t key, std::vector<uint8_t>& ps1)
{
	uint64_t h = 0;
	for(int i=0; i < ps1.size(); ++i)
	{
		uint64_t bit = 0;
		bit = ((key >> (64 - ps1[i])) & 1) << (27-i);
		h = h | bit;
	}
	return h;
}

void SubkeyGenerator::permutate(uint64_t& key)
{
	uint64_t in = key;
	key = 0;

	for(int i=0; i < ps2.size(); ++i)
	{
		uint8_t per = 56 - ps2[i];
		uint64_t one = 1;
		uint64_t bit = (in >> per) & one;
		key	|= (bit << i);
	}
}
