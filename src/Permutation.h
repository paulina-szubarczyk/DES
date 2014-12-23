#ifndef INCLUDE_PERMUTATION_H_
#define INCLUDE_PERMUTATION_H_

#include <vector>
#include <cstdint>

class Permutation {
public:

	Permutation();

	virtual ~Permutation();

	virtual uint64_t permutate(uint64_t msg) ;

protected:

	std::vector<unsigned> permutation;

};

#endif /* INCLUDE_PERMUTATION_H_ */
