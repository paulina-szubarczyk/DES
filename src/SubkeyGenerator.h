#ifndef INCLUDE_SUBKEYGENERATOR_H_
#define INCLUDE_SUBKEYGENERATOR_H_
#include <cstdint>
#include <vector>

class SubkeyGenerator {
public:
	SubkeyGenerator(uint64_t key);
	virtual ~SubkeyGenerator();

	uint64_t generateKey(uint8_t i);

//private:
	std::vector<uint8_t> ps2;
	uint64_t C, D;

	uint64_t generate_half(uint64_t key, std::vector<uint8_t>& ps1);
	void permutate(uint64_t& key);
};

#endif /* INCLUDE_SUBKEYGENERATOR_H_ */
