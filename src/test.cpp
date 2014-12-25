#include "test.h"
#include <boost/test/unit_test.hpp>

#include "InitialPermutation.h"
#include "FeistelFunction.h"
#include "FinalPermutation.h"
#include "SubkeyGenerator.h"
#include "utils.h"
#include "DES.h"

struct msg
{
	msg() : smsg {'1','2','3','4','5','6','7','8','\0'} {}

	uint8_t smsg[9];
	uint8_t scr[9];
	uint8_t skey[9];
	uint64_t m, cr, key;
};

BOOST_AUTO_TEST_SUITE(utils_suite)
BOOST_AUTO_TEST_CASE(write)
{
	msg m;

	BOOST_CHECK_EQUAL(m.m = utils::write_to_uint64_t(m.smsg), 3544952156018063160);

	utils::write_to_uint8_t(m.m,m.scr);

	BOOST_CHECK_EQUAL(std::string(m.scr,m.scr+8), std::string(m.smsg, m.smsg+8));
}

BOOST_AUTO_TEST_CASE(to_zero)
{
	msg m;

	m.m = utils::write_to_uint64_t(m.smsg);

	utils::set_to_zero(m.smsg,8);
	m.m = utils::write_to_uint64_t(m.smsg);

	BOOST_CHECK_EQUAL(m.m,0);
}

BOOST_AUTO_TEST_CASE(halfs)
{
	msg m;

	m.m = utils::write_to_uint64_t(m.smsg);

	BOOST_CHECK_EQUAL(utils::left_half(m.m),825373492);
	BOOST_CHECK_EQUAL(utils::right_half(m.m),892745528);
	BOOST_CHECK_EQUAL(utils::merge(
			utils::left_half(m.m),utils::right_half(m.m)),
			3544952156018063160);
}

BOOST_AUTO_TEST_CASE(parity_bit)
{
	msg m;
	m.key = utils::generate_key();
	utils::write_to_uint8_t(m.key,m.skey);
	utils::print_as_uint(m.skey,8);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(key)

BOOST_AUTO_TEST_CASE(key_generator)
{
	uint64_t key = 410694521981572927;
	SubkeyGenerator g(key);

	BOOST_CHECK_EQUAL(g.C,52661164);
	BOOST_CHECK_EQUAL(g.D,204331662);
}

BOOST_AUTO_TEST_CASE(permutacje)
{
	uint64_t m = 3544952156018063160;
	uint64_t c = 0;
	uint64_t m1 = 0;

	InitialPermutation ip1;
	FinalPermutation ip2;

	c = ip1.permutate(m);
	m1 = ip2.permutate(c);

	BOOST_CHECK_EQUAL(m1,m);
}

BOOST_AUTO_TEST_CASE(des)
{
	uint64_t key = 410694521981572927;
	uint64_t m = 3544952156018063160;

	DES des(key);

	BOOST_CHECK(des.encrypt(m) != m);

	BOOST_CHECK_EQUAL(des.decrypt(des.encrypt(m)),m);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(feistel)

BOOST_AUTO_TEST_CASE(expand)
{
	uint64_t R = 4086647613;
	ExpansionFunction().expand(R);
	BOOST_CHECK_EQUAL(R,275413345855995);
}

BOOST_AUTO_TEST_CASE(permutate)
{
	uint64_t R = 771924321;
	FeistelPermutation().permutate(R);
	BOOST_CHECK_EQUAL(R,1096298128);

	uint64_t R2 = 1309444559;
	FeistelPermutation().permutate(R2);
	BOOST_CHECK_EQUAL(R2,1494923377);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(files)

BOOST_AUTO_TEST_CASE(read_write)
{
	std::vector<uint8_t> v,v1;
	utils::read_from_file("msg",v);
	std::vector<uint64_t> v64;
	utils::write_to_uint64_t(v,v64);
	utils::write_to_uint8_t(v64,v1);
	utils::write_to_file("msg2",v1);
}

BOOST_AUTO_TEST_CASE(DES_to_file)
{

	std::cout << "==================BEGIN===================\n";
	std::vector<uint8_t> v,v1,v2,v3;

	utils::read_from_file("msg",v);

	std::vector<uint64_t> v64m1, v64c1, v64c2, v64m2;

	utils::write_to_uint64_t(v,v64m1);

	DES des(utils::generate_key());

	for(auto m : v64m1)
		v64c1.push_back(des.encrypt(m));

	utils::write_to_uint8_t(v64c1,v1);

	utils::write_to_file("encrypt",v1);

	utils::read_from_file("encrypt",v2);

	utils::write_to_uint64_t(v2,v64c2);

	for(auto c : v64c2)
		v64m2.push_back(des.decrypt(c));

	v64m2.pop_back();
	utils::write_to_uint8_t(v64m2,v3);

	utils::write_to_file("decrypt",v3);
}

BOOST_AUTO_TEST_SUITE_END()
