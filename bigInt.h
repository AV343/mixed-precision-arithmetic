#ifndef BIGINT_H
#define BIGINT_H
#include <vector>

class bigInt{
	public:
		bigInt(std::vector<unsigned int> blocks, bool is_positive); // Array Constructor
		bigInt(int k); // 0 Constructor
		
		// Fields needed for arithmetic
		std::vector<unsigned int> blocks;
		bool is_positive;
		int k;

		unsigned int get_block(int i, unsigned int if_fails=0);
		bool set_block(int i, unsigned int n);
		std::string toString();
	
	friend bigInt operator+(bigInt a, bigInt b);
	friend bigInt operator<<(bigInt a, int n);
};

#endif
