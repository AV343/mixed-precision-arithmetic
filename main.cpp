#include "bigInt.h"
#include <vector>
#include <iostream>

void test(){
	std::vector<unsigned int> blocks = {0xFFFFFFFF, 0xFFFFFFFA, 0xFFFFFFF0};
	bigInt num(blocks, true);
	std::cout << "Number of blocks: " << num.k << std::endl;
	for (int i=0; i<num.k; i++)
		std::cout << "The " << i << "th block is: " << num.get_block(i) << std::endl;
}

int main(){
	//std::cout << "0xFFFF'FFFF + 0x0000'0001 = " << 0xFFFFFFFF + 0x00000001 << std::endl;
	bigInt a({0xFFFF0000, 0xFFFFFFFF}, true);
	bigInt b({0x0000FFFF, 0x00000001}, true);
	bigInt c = a+b;
	std::cout << "a has " << a.k << " blocks" << std::endl;
	std::cout << "b has " << b.k << " blocks" << std::endl;
	std::cout << "a+b has " << c.k << " blocks" << std::endl;
	std::cout << a.toString() << " + " << b.toString() << " = " << c.toString() << std::endl;
}
