#ifndef INCLUDE_FEISTELPERMUTATION_H_
#define INCLUDE_FEISTELPERMUTATION_H_
#include "Permutation.h"

class FeistelPermutation : public Permutation {
public:
	FeistelPermutation();
	virtual ~FeistelPermutation();
	virtual void permutate(uint64_t& inout) ;

protected:

	std::vector<unsigned> permutation;
};

#endif /* INCLUDE_FEISTELPERMUTATION_H_ */
