#include <iostream>
#include "bigInt.h"

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

bigInt operator<<(int n){
	int num_blocks = this->k;
	while (n >= 32){
		n -= 32;
		num_blocks++;
	}
	first_block = this->blocks[0] >> (32-n);
	if (first_block > 0) num_blocks++;
	bigInt res = bigInt(num_blocks);
	res.blocks[0] = first_block;

	// Change res, not the initial number
	for(int i=1; i<this->k; i++){
		unsigned int block = this->blocks[i];
		this->blocks[i] = block << n;
		if (block >= 0x800000000){
			this->blocks[i-1] += 1;
		}
	}
}

bool operator==(bigInt a, bigInt b){
	if (a.k != b.k) return false;
	for (int i=0; i<a.k; i++){
		if (a.blocks[i] != b.blocks[i]) return false;
	}
	return true;
}

bool operator!=(bigInt a, bigInt b){
	if (a.k != b.k) return true;
	for (int i=0; i<a.k; i++){
		if (a.blocks[i] != b.blocks[i]) return true;
	}
	return false;
}

bigInt operator&(bigInt a, bigInt b){
	pass
}

bigInt operator+(bigInt a, bigInt b){
	while (b!=0){
		int carry = 
	}
}

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
