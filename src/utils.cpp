#include "utils.h"


void utils::set_to_zero(uint8_t* w, int size)
{
	for(int i = 0; i < size; ++i)
		w[i] = 0;
}

void utils::print_as_uint(uint8_t* w, int size)
{
	for(int i=size-1; i>=0; --i)
	{
		std::cout << "msg: " << (uint)(w[i]) << " | ";
	}
	std::cout << std::endl;
}

uint64_t utils::create_mask(uint8_t w, int shift)
{
	uint64_t tmp = 0;
	tmp = (uint64_t)w << shift;
	return tmp;
}

void utils::write_to_uint8_t(uint64_t msg, uint8_t* cmsg)
{

	cmsg[8] = '\0';

	for(int i=7; i>=0; --i)
	{
		std::cout << "msg: " << (int)((uint8_t)msg) << " | ";

		cmsg[i] = uint8_t(msg);
		msg >>= 8;
	}
}

uint64_t utils::left_half(uint64_t i_64)
{
	return (i_64 >> 32) ;
}

uint64_t utils::right_half(uint64_t i_64)
{
	i_64 <<= 32;
	return (i_64 >> 32) ;
}

uint64_t utils::merge(uint64_t left, uint64_t right)
{
	return (left << 32) | right;
}

void utils::print_uint64(uint64_t i_64)
{
	std::cout << "uint64_t: " << i_64 << std::endl;
}

void utils::set_parity_bit(uint64_t & bit)
{
	bit = bit << 1;
	uint8_t count = 0;
	for(uint8_t i=0; i<7; ++i)
		if(bit & (1 << i))
			++count;

	if (count % 2)
		bit |= 1;
}

uint64_t utils::generate_key()
{
	//	srand (time(NULL));
	uint64_t key = 0;

	for(int i = 0; i < 8; ++i)
	{
		// <1,127>
		uint64_t p= rand() % 126 + 1;
		utils::set_parity_bit(p);
		std::cout << "p:    " << p << " | ";
		key = key | (p << (56 - i*8));
	}
	std::cout << "key:    " << key << " \n";
	return key;
}

uint64_t utils::write_to_uint64_t(uint8_t* msg)
{
	uint64_t msg_64 = 0;

	for (int i=0; i < 8; ++i)
		msg_64 |= create_mask(msg[7-i], i*8);

	std::cout <<"msg_64: " <<  msg_64 << std::endl;
	return msg_64;
}

void utils::write_to_uint64_t(const std::vector<uint8_t>& msg, std::vector<uint64_t>& msg64)
{
	uint64_t tmp = 0;

	for (uint i=0; i < msg.size(); ++i)
	{
		if (i>0 && !(i%8))
		{
			msg64.push_back(tmp);
			std::cout <<"tmp: " <<  tmp << std::endl;
			tmp = 0;
		}

		tmp |= ((uint64_t)msg[i] << (i%8)*8);
	}

	uint8_t pad = (msg.size()%8);

	if(pad)
	{
		std::vector<uint8_t> padv(8,8-pad);
		std::copy(msg.end()-pad, msg.end(),padv.begin());

		utils::print_vector(padv);
		tmp = 0;

		for (uint i=0; i < 8; ++i)
		{
			tmp |= ((uint64_t)padv[i] << (i)*8);
		}
		std::cout <<"size: " << padv.size() << " tmp: " <<  tmp << std::endl;

		msg64.push_back(tmp);
	}
	utils::print_vector(msg64);
}


void utils::write_to_uint8_t(const std::vector<uint64_t>& msg,
		std::vector<uint8_t>& cmsg)
{
	std::cout <<"size: " << msg.size() << std::endl;

	for(uint i=0; i < msg.size(); ++i)
	{
		uint64_t m_copy(msg[i]);

		for(int j=7; j>=0; --j)
		{
			cmsg.push_back(uint8_t(m_copy));
			m_copy >>= 8;
			std::cout <<"m_copy: " << int(uint8_t(m_copy)) << std::endl;

		}
	}
	utils::print_vector(msg);
	std::cout <<"size: " << cmsg.size() << std::endl;

	cmsg.push_back(10); //EOL
	utils::print_vector(cmsg);
}

bool utils::read_from_file(char* file_name, std::vector<uint8_t>& v)
{
	std::ifstream file(file_name, std::ios::binary);
	v.resize(file.tellg());
	v.assign(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
	utils::print_vector(v);
}

bool utils::write_to_file(char* file_name, const std::vector<uint8_t>& v)
{
	std::ofstream file(file_name, std::ios::binary);
	std::copy(v.begin(), v.end(), std::ostreambuf_iterator<char>(file));
}
