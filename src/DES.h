#ifndef SRC_DES_H_
#define SRC_DES_H_

#include <cstdint>
#include "InitialPermutation.h"
#include "FeistelFunction.h"
#include "FinalPermutation.h"
#include "SubkeyGenerator.h"

class DES {
public:
	DES(uint64_t key);

	uint64_t encrypt(uint64_t m);
	uint64_t decrypt(uint64_t c);
private:
	uint64_t k;

	InitialPermutation ip;
	FeistelFunction f;
	FinalPermutation ip_1;
	SubkeyGenerator g;

	uint64_t shift(uint64_t L, uint64_t R);
	void round(uint8_t i, uint64_t& c);
};

#endif /* SRC_DES_H_ */
