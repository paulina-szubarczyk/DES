#ifndef SRC_SBOXES_H_
#define SRC_SBOXES_H_
#include <vector>
#include <cstdint>

class SBoxes {
public:
	SBoxes();
	virtual ~SBoxes();

	void calculate(uint64_t &inout);

private:
	static uint8_t S[8][4][16];

	uint8_t sboxe(uint64_t i_64, uint8_t i_8);
};


#endif /* SRC_SBOXES_H_ */
