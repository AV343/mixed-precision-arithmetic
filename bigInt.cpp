#include <iostream>
#include "bigInt.h"

// Constructors
bigInt::bigInt(std::vector<unsigned int> blocks, bool is_positive){
	//std::cout << "The size of a boolean is " << sizeof(bool);
	this->blocks = blocks;
	this->k = blocks.size();
	this->is_positive = is_positive;
}

bigInt::bigInt(int k){
	this->blocks = std::vector<unsigned int>(k, 0);
	this->k = k;
}

// Getter and setter
unsigned int bigInt::get_block(int i, unsigned int if_fails){
	if (i < this->k) return this->blocks[this->k - 1 - i];
	else return if_fails;
}

bool bigInt::set_block(int i, unsigned int n){
	if (i < this->k){
		this->blocks[this->k - 1 - i] = n;
		return true;
	}
	else return false;
}


// toString
std::string bigInt::toString(){
	std::string res;
	for (int i=0; i<this->k; i++){
		std::string tmp(8, '0');
		unsigned int n = this->blocks[i];
		for (int j=7; j>=0; j--){
			//std::cout << "Remainder: " << n%16 << std::endl;
			tmp[j] = "0123456789ABCDEF"[n%16];
			//std::cout << "Character: " << tmp[j] << std::endl;
			n/=16;
		}
		res.append(tmp);
		if (i+1!=this->k) res.append(",");
	}
	return res;
}

// Bit shifts
bigInt operator<<(const bigInt& a, unsigned int n){
	unsigned int num_empty = n/32;
	n %= 32;
	int k = a.k;
	bigInt ans = bigInt(k);
	std::vector<unsigned int> res = ans.blocks;

	// Shifting over the blocks
	for (int i=0; i<num_empty; i++){
		res[i] = (i+num_empty > k-1) ? 0 : a.blocks[i+num_empty];
	}

	// Now we do actual bit shifting by n<32
	for(int i=0; i<k; i++){
		unsigned int end = i==k-1 ? 0 : (res[i+1] >> (32-n));
		res[i] = (res[i] << n) | end;
	}
	return ans;
}

bigInt operator>>(const bigInt& a, unsigned int n){
	unsigned int num_empty = n/32;
	n %= 32;
	int k = a.k;
	bigInt ans = bigInt(k);
	std::vector<unsigned int> res = ans.blocks;

	// Shifting over the blocks
	for (int i = k-1; i >= k-num_empty; i--){
		res[i] = (i-num_empty < 0) ? 0 : a.blocks[i-num_empty];
	}

	// Now we do actual bit shifting by n<32
	for(int i=k-1; i>=0; i--){
		unsigned int end = i==0 ? 0 : (res[i-1] << (32-n));
		res[i] = (res[i] >> n) | end;
	}
	return ans;
}


// Bitwise logic
bigInt operator&(const bigInt& a, const bigInt& b){
	int ma = std::max(a.k, b.k);
	bigInt res = bigInt(ma);
	for (int i = 0; i<ma; i++){
		unsigned int a_block = a.k-1-i<0 ? 0 : a.blocks[a.k-1-i];
		unsigned int b_block = b.k-1-i<0 ? 0 : b.blocks[b.k-1-i];
		res.blocks[ma-1-i] = a_block & b_block;
	}
	return res;
}

bigInt operator|(const bigInt& a, const bigInt& b){
	int ma = std::max(a.k, b.k);
	bigInt res = bigInt(ma);
	for (int i = 0; i<ma; i++){
		unsigned int a_block = a.k-1-i<0 ? 0 : a.blocks[a.k-1-i];
		unsigned int b_block = b.k-1-i<0 ? 0 : b.blocks[b.k-1-i];
		res.blocks[ma-1-i] = a_block | b_block;
	}
	return res;
}

bigInt operator^(const bigInt& a, const bigInt& b){
	int ma = std::max(a.k, b.k);
	bigInt res = bigInt(ma);
	for (int i = 0; i<ma; i++){
		unsigned int a_block = a.k-1-i<0 ? 0 : a.blocks[a.k-1-i];
		unsigned int b_block = b.k-1-i<0 ? 0 : b.blocks[b.k-1-i];
		res.blocks[ma-1-i] = a_block ^ b_block;
	}
	return res;
}

// Equality/Inequality testing
bool operator==(const bigInt& a, const bigInt& b){
	for (int i=0; i<a.k; i++){
		if (a.blocks[i] != b.blocks[i]) return false;
	}
	return true;
}

bool operator!=(const bigInt& a, const bigInt& b){
	for (int i=0; i<a.k; i++){
		if (a.blocks[i] != b.blocks[i]) return true;
	}
	return false;
}

// Arithmetic operators
bigInt operator+(bigInt a, bigInt b){
	while (b!=0){
		bigInt carry = a & b;
		a = a^b;
		b = carry << 1;
	}
	return a;
}

/*
bigInt operator+2(bigInt a, bigInt b){
	std::cout << "Starting add" << std::endl;
	int new_k = std::max(a.k, b.k);
	bigInt c = bigInt(new_k);
	bigInt carries = bigInt(new_k+1);
	bool add_again = false;
	
	std::cout << "c.k = " << c.k << std::endl;	
	std::cout << "carries.k = " << carries.k << std::endl;
	for (int i=0; i<c.k; i++){
		c.set_block(i, a.get_block(i) + b.get_block(i));
		//std::cout << i << "th block of c is " << c.get_block(i) << std::endl;
		//std::cout << i << "th block of a is " << a.get_block(i) << std::endl;

		if (c.get_block(i) < a.get_block(i, b.get_block(i))){
			carries.set_block(i+1, 1);
			add_again = true;
			std::cout << "Carrying to block " << i+1 << std::endl;
		}
	}
	if (add_again) return c + carries;
	else return c;
}
*/

/*
bigInt toom3(bigInt m, bigInt n){
	m_split = split(m, 3);
	m0 = m_split[0];
	m1 = m_split[1];
	m2 = m_split[2];

	n_split = split(n, 3);
	n0 = n_split[0];
	n1 = n_split[1];
	n2 = n_split[2];

	p_0 = m0 + m2;
	p0 = m0
	p1 = p0 + m1;
	pn1 = p0 - m1;
	pn2 = (pn1 + m2)*2 - m0;
	pinf = m2;

	q_0 = n0 + n2;
	q0 = n0
	q1 = q0 + n1;
	qn1 = q0 - n1;
	qn2 = (qn1 + n2)*2 - n0;
	qinf = n2;

}
*/
