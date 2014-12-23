#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_
#include <cstdint>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iterator>
#include <algorithm>

class utils {
public:

	static void set_to_zero(uint8_t* w, int size);
	static void print_as_uint(uint8_t* w, int size);
	static uint64_t create_mask(uint8_t w, int shift);
	static uint64_t write_to_uint64_t(uint8_t* msg);
	static void write_to_uint64_t(const std::vector<uint8_t>& msg, std::vector<uint64_t>& msg64);
	static void write_to_uint8_t(uint64_t  msg, uint8_t* cmsg);
	static void write_to_uint8_t(const std::vector<uint64_t>&  msg, std::vector<uint8_t>& cmsg);
	static uint64_t left_half(uint64_t  i_64);
	static uint64_t right_half(uint64_t  i_64);
	static uint64_t merge(uint64_t  left, uint64_t  right);
	static void print_uint64(uint64_t  i_64);
	static void set_parity_bit(uint64_t & bit);
	static uint64_t generate_key();

	static bool read_from_file(char* file_name, std::vector<uint8_t>& v);
	static bool write_to_file(char* file_name, const std::vector<uint8_t>& v);

private:
	template<class T> static void print_vector(std::vector<T> v)
	{
		std::cout << "vector\n";
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, ","));
	}
};

#endif /* SRC_UTILS_H_ */
