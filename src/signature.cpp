#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include "utils.h"
#include "DES.h"
#include <ctime>

int main(int argc, char** argv)
{
	srand (time(NULL));

	std::vector<uint8_t> cry8, e_key8, key8;
	std::vector<uint64_t> msg, msg64, cry64, keys;
	uint64_t keyt = 0;

	char* e_file_name = "encrypt";
	char* e_keys_file_name = "encrypt_key";
	char* keys_file_name = "key";
	char* selected_keys_file = "selected";
	char* key_numbers = "keys_numbers";

	std::string file_name;
	int n;


	utils::get_signer_params(argv, argc, n, file_name);

	utils::read_msg_to_vector(file_name, msg64);

	utils::write_header_to_file(e_file_name, 0, true);
	utils::write_header_to_file(e_keys_file_name, 0, true);
	utils::write_header_to_file(keys_file_name, 0, true);
	utils::write_header_to_file(selected_keys_file, 0, true);

	for (int i=0; i<n; ++i)
		keys.push_back(utils::generate_key());

	for (auto key : keys)
	{
//		std::cout << "\nkey " << key << std::endl;

		DES des(key);
		uint64_t public_key = 0;

		for(auto m : msg64)
			cry64.push_back(des.encrypt(m));

		public_key = des.encrypt(keyt++);

		utils::write_to_uint8_t(cry64,cry8);
		utils::write_to_uint8_t(public_key,e_key8);
		utils::write_to_uint8_t(key,key8);

		utils::write_header_to_file(e_file_name,cry8.size());
		utils::write_header_to_file(e_keys_file_name,e_key8.size());
		utils::write_header_to_file(keys_file_name,key8.size());

		utils::write_to_file(e_file_name, cry8);
		utils::write_to_file(e_keys_file_name, e_key8);
		utils::write_to_file(keys_file_name, key8);

		cry64.clear();
		cry8.clear();
		e_key8.clear();
		key8.clear();
	}

	std::cout << "\nEncryption finished\n";

	int knumber =  n/2 + 1;
	std::cout << "Select " << knumber << " keys numbers.\n";
	int i = 0;
	std::vector<int> ikey;

	while ( i < knumber)
	{
		std::string skeys;
		std::cin >> skeys;
		int k = atoi(skeys.c_str());
		if (k > 0 && k <= n)
		{
			ikey.push_back(k);
			++i;
		}
		else
			std::cout << "bad number\n";
	}

	std::vector<uint64_t> selected_keys;

	for (int k=0; k < ikey.size(); ++k)
		selected_keys.push_back(keys[ikey[k]]);

	for (int k=0; k < selected_keys.size(); ++k)
	{
		utils::write_to_uint8_t(selected_keys[k],key8);
		utils::write_header_to_file(selected_keys_file,key8.size());
		utils::write_to_file(selected_keys_file, key8);
		key8.clear();
	}
	utils::write_keys_numbers(key_numbers,ikey);

	return 0;
}
