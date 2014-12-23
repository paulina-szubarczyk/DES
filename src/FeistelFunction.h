#ifndef INCLUDE_FEISTELFUNCTION_H_
#define INCLUDE_FEISTELFUNCTION_H_

#include "ExpansionFunction.h"
#include "FeistelPermutation.h"
#include "SBoxes.h"

class FeistelFunction {
public:
	FeistelFunction();

	uint64_t calculate(uint64_t Ri, uint64_t Ki);

private:
	ExpansionFunction E;
	SBoxes S;
	FeistelPermutation P;
};

#endif /* INCLUDE_FEISTELFUNCTION_H_ */
