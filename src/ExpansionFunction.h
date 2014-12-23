#ifndef INCLUDE_EXPANSIONFUNCTION_H_
#define INCLUDE_EXPANSIONFUNCTION_H_
#include <vector>
#include <cstdint>

class ExpansionFunction {
public:
	ExpansionFunction();
	virtual ~ExpansionFunction();

	void expand(uint64_t& inout);

private:
	std::vector<unsigned> permutation;
};

#endif /* INCLUDE_EXPANSIONFUNCTION_H_ */
