#ifndef BIGINT_H
#define BIGINT_H
#include <vector>

class bigInt{
	private:
		// Fields needed for arithmetic
		std::vector<unsigned int> blocks;
		bool is_positive;
		int k;

	public:
		bigInt(std::vector<unsigned int> blocks, bool is_positive); // Array Constructor
		bigInt(int k); // 0 Constructor

		unsigned int get_block(int i, unsigned int if_fails=0);
		bool set_block(int i, unsigned int n);
		std::string toString();
		void extend(bigInt a);
		
		friend bigInt operator<<(const bigInt& a, unsigned int n);
		friend bigInt operator>>(const bigInt& a, unsigned int n);

		friend bigInt operator&(const bigInt& a, const bigInt& b);
		friend bigInt operator|(const bigInt& a, const bigInt& b);
		friend bigInt operator^(const bigInt& a, const bigInt& b);

		friend bool operator==(const bigInt& a, const bigInt& b);
		friend bool operator!=(const bigInt& a, const bigInt& b);

		friend bigInt operator+(bigInt a, bigInt b);
		friend bigInt operator-(bigInt a, bigInt b);
		friend bigInt operator*(bigInt a, bigInt b);
		//friend bigInt operator**(bigInt a, bigInt b);
};

#endif
