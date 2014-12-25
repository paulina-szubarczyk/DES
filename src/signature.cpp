#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include "utils.h"
#include "DES.h"

int main(int argc, char** argv)
{
	char* file_name = "msg";
	// number of keys to generate
	int n;
	int arg;

	while ( (arg = getopt(argc, argv, "fn:")) != -1)
	{
		switch(arg)
		{
		case 'f':
//			std::cout << optarg << std::endl;
			break;
		case 'n':
			n = atoi(optarg);
			break;
		default:
			std::cout <<" usage: \n -f name of the file with msg \n -n number of keys to generate\n";
			abort();
		}
	}


	std::cout << "n : " << n << "\nfile name : " << file_name << "\n";

	std::vector<uint64_t> keys(n);
	for (int i=0; i<n; ++i)
		keys.push_back(utils::generate_key());

	std::vector<uint64_t> msg;

	std::vector<uint8_t> msg8, cry8, key8;

	utils::read_from_file("msg",msg8);

	std::vector<uint64_t> msg64, cry64, public_keys;

	utils::write_to_uint64_t(msg8,msg64);

	char* e_file_name = "encrypt";

	utils::write_header_to_file(e_file_name,0,true);

	uint64_t public_key = 0;

	for (auto key : keys)
	{
		DES des(key);

		for(auto m : msg64)
			cry64.push_back(des.encrypt(m));

		public_keys.push_back(des.encrypt(public_key++));

		utils::write_to_uint8_t(cry64,cry8);

		utils::write_header_to_file(e_file_name,cry8.size());

		utils::write_to_file(e_file_name, cry8);

		cry64.clear();

		cry8.clear();
	}

	utils::write_to_uint8_t(public_keys, key8);

	utils::write_keys_to_file(e_file_name, key8);

	std::cout << "Encryption finished\n";

	return 0;
}
