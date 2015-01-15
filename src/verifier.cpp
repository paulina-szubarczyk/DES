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

	char* e_file_name = "encrypt";
	char* e_keys_file_name = "encrypt_key";
	char* keys_file_name = "key";
	char* selected_keys_file = "selected";
	char* key_numbers = "keys_numbers";

	std::string file_name, msg_file;
	int n;

	std::vector<std::vector<uint64_t> > cry;
	std::vector<uint64_t> selected_keys, keys, pkeys, msg64;
	std::vector<uint8_t> msg8;
	std::vector<int> ikey;
	std::vector<bool> verifie;

	utils::get_verifier_params(argv, argc, n, file_name, msg_file);
	utils::read_cryptogram_to_vector(file_name, cry);
	utils::read_msg_to_vector(msg_file, msg64);

	utils::read_key_to_vector(keys_file_name, keys);
	utils::read_key_to_vector(selected_keys_file, selected_keys);
	utils::read_key_to_vector(e_keys_file_name, pkeys);
	utils::read_keys_numbers(key_numbers,ikey);

	for(int i=0; i<selected_keys.size(); ++i)
	{
		std::vector<uint64_t> message;
		DES des(selected_keys[i]);

		std::cout << "\nkey: " << selected_keys[i] << std::endl;

		for(auto cryptogram : cry[ikey[i]])
		{
			message.push_back(des.decrypt(cryptogram));
		}
		message.pop_back();

		uint64_t public_key = des.decrypt(pkeys[ikey[i]]);

		bool verifing1 = public_key == ikey[i] ;
		bool verifing2 = message == msg64 ;
		std::string pkey_verifier = verifing1 ? " True " : " False ";
		std::string msg_verifier = verifing2 ? " True " : " False ";

		verifie.push_back(verifing1 && verifing2);

		std::cout << "PUBLIC KEY " << public_key << pkey_verifier << std::endl;

		std::cout << "ENCRYPTED MESSAGE " << std::endl;
		utils::print_vector(message);

		std::cout << "ORYGINAL_MESSAGE " << std::endl;
		utils::print_vector(msg64);

		std::cout << "MESSAGES " << msg_verifier << std::endl;

		message.clear();
	}

	if (std::find(verifie.begin(),verifie.end(),false) == verifie.end())
		std::cout << "\nMessage accepted\n";
	else
		std::cout << "\nMessage neglected\n";

	utils::write_to_uint8_t(msg64,msg8);
	utils::print_vector(msg8);
}
