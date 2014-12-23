#include "FeistelFunction.h"
#include <iostream>
FeistelFunction::FeistelFunction() {
	// TODO Auto-generated constructor stub

}



uint64_t FeistelFunction::calculate(uint64_t Ri, uint64_t Ki)
{
	// permutacja rozszerzająca
	E.expand(Ri);
//	std::cout << "R1: " << Ri << "\t" ;

	// suma modulo 2 z podkluczem
	Ri ^= Ki;
//	std::cout << "R2: " << Ri << "\t" ;

	// sboxy
	S.calculate(Ri);
//	std::cout << "R3: " << Ri << "\t" ;

	// permutacja feistela
	P.permutate(Ri);
//	std::cout << "R4: " << Ri << "\n" ;

	return Ri;
}

