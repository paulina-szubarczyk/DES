#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_
#include <cstdint>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>

class utils {
public:

	static void set_to_zero(uint8_t* w, int size);
	static void print_as_uint(uint8_t* w, int size);
	static uint64_t create_mask(uint8_t w, int shift);

	static uint64_t write_to_uint64_t(uint8_t* msg);
	static uint64_t write_to_uint64_t(std::vector<uint8_t>& msg);

	static void read_msg_to_vector(std::string file_name, std::vector<uint64_t>& msg64);
	static void read_cryptogram_to_vector(std::string file_name, std::vector<std::vector<uint64_t> >& msg64);
	static void read_key_to_vector(std::string file_name, std::vector<uint64_t>& msg64);

	static void write_to_uint64_t(const std::vector<uint8_t>& msg, std::vector<uint64_t>& msg64);
	static void write_to_uint8_t(uint64_t  msg, std::vector<uint8_t>& cmsg);
	static void write_to_uint8_t(const std::vector<uint64_t>&  msg, std::vector<uint8_t>& cmsg);

	static uint64_t left_half(uint64_t  i_64);
	static uint64_t right_half(uint64_t  i_64);
	static uint64_t merge(uint64_t  left, uint64_t  right);
	static void print_uint64(uint64_t  i_64);
	static void set_parity_bit(uint64_t & bit);
	static uint64_t generate_key();

	static void get_verifier_params(char** argv, int argc, int& n, std::string& file_name_cryptogram, std::string& file_name_msg);
	static void get_signer_params(char** argv, int argc, int& n, std::string& file_name);

	static bool read_cryptogram_from_file(std::string file_name, std::vector<std::vector<uint8_t> > & v);
	static bool read_msg_from_file(std::string file_name, std::vector<uint8_t>& v);
	static bool write_to_file(std::string file_name, const std::vector<uint8_t>& v);
	static bool write_header_to_file(std::string file_name, int message_size, bool new_file = false);

	static bool write_keys_numbers(std::string file_name, std::vector<int>& numbers);
	static bool read_keys_numbers(std::string file_name, std::vector<int>& numbers);

	template<class T> static void print_vector(std::vector<T> v)
	{
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, ","));
		std::cout << "\n";

	}
};

#endif /* SRC_UTILS_H_ */
