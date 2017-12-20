#include "primality_tests.cpp"
#include <cmath>
#include <utility>

uint64_t pseudo_random_prime_generator(int bits_size,std::string primality_test_string);
class RSA{
private:
	std::string primality_test;
	int key_length;
	uint64_t p,q;
	uint64_t n,phi;
	uint64_t private_key,public_key;

	void generate_and_assign_keys();
	uint64_t encrypt_block(uint64_t plain_text_block);
	uint64_t decrypt_block(uint64_t cipher_text_block);
public:
	
	RSA(int key_length,std::string primality_test_string){
		this->key_length = key_length;
		this->primality_test.assign(primality_test_string);
		
		this->p = pseudo_random_prime_generator(key_length/2,primality_test_string);
		this->q = pseudo_random_prime_generator(key_length/2,primality_test_string);
		
		while(this->p==this->q) {
			this->q = pseudo_random_prime_generator(key_length/2,primality_test_string);
		}

		this->n = p*q;
		this->phi = (p-1)*(q-1);

		generate_and_assign_keys();

	}
	uint64_t getPublicKey();

	std::string encrypt_message(std::string plain_text);
	std::string decrypt_message(std::string cipher_text);
};

uint64_t RSA::getPublicKey(){
	return public_key;
}

void RSA::generate_and_assign_keys(){
	srand(time(NULL));
	uint64_t n = rand()%(this->phi-2) + 1;
	while(gcd(n,this->phi)!= 1){
		n = rand()%(this->phi-2) + 1;
	}
	this->public_key = n;
	this->private_key = modular_inverse(n,this->phi);
}

uint64_t RSA::encrypt_block(uint64_t plain_text_block){
	uint64_t cipher_text_block;
	cipher_text_block = modular_exponentiation(plain_text_block,this->public_key,this->n);
	return cipher_text_block;
}

uint64_t RSA::decrypt_block(uint64_t cipher_text_block){
	uint64_t plain_text_block;
	plain_text_block = modular_exponentiation(cipher_text_block,this->private_key,this->n);
	return plain_text_block;
}
std::string RSA::encrypt_message(std::string plain_text){
	/*
		Multiplexing:
			convert 8 characters into an uint64_t variable
			thus creating an array of uint64_t
			try using reinterpret_cast for this (bitset if required)
	*/


	/*
		Blockwise Encryption
			treat each element as a block of plain_text
			encrypt into cipher_text array of int64_t
	*/

	/*
		Demultiplexing:
			convert each in64_t of cipher_text array of int64_t
			thus creating a string of required cipher text
			try using reinterpret_cast for this (bitset if required)
	*/
}

std::string RSA::decrypt_message(std::string cipher_text){
	/*
		Multiplexing:
			convert 8 characters into an uint64_t variable
			thus creating an array of uint64_t
			try using reinterpret_cast for this (bitset if required)
	*/


	/*
		Blockwise Decryption
			treat each element as a block of cipher_text
			decrypt into plain_text array of int64_t
	*/

	/*
		Demultiplexing:
			convert each in64_t of plain_text array of int64_t
			thus creating a string of required plain_text
			try using reinterpret_cast for this (bitset if required)
	*/
}

uint64_t pseudo_random_prime_generator(int bits_size, std::string primality_test_string){
	srand(time(NULL));
	uint64_t range = pow(2,bits_size-1);
	uint64_t num = range + rand()%(range);
	if(num%2==0)
		num++;
	while(primality_test(num,primality_test_string)==false){
		num+=2;
		if(num>=range*2)
			num = range + rand()%(range);
	}
	return num;
}

