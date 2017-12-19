#include "primality_tests.cpp"
#include "prime_helper.cpp"
#include <cmath>
#include <utility>

int64_t pseudo_random_prime_generator(int bits_size,primality_test_string);
class RSA{
private:
	std::string primality_test;
	int key_length;
	int64_t p,q;
	int64_t n,phi;
	int64_t private_key,public_key;

	void generate_and_assign_keys();
	int64_t encrypt_block(int64_t plain_text_block);
	int64_t decrypt_block(int64_t cipher_text_block);
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
};

void RSA::generate_and_assign_keys(){
	srand(time(NULL));
	int64_t n = rand()%(this->phi-2) + 1;
	while(gcd(n,this->phi)!= 1){
		n = rand()%(this->phi-2) + 1;
	}
	this->public_key = n;
	this->private_key = modular_inverse(n,this->phi);
}

int64_t RSA::encrypt_block(int64_t plain_text_block){
	int64_t cipher_text_block;
	cipher_text_block = modular_exponentiation(plain_text_block,this->public_key,this->n);
	return cipher_text_block;
}

int64_t RSA::decrypt_block(int64_t cipher_text_block){
	int64_t plain_text_block;
	plain_text_block = modular_exponentiation(cipher_text_block,this->private_key,this->n);
	return plain_text_block;
}

int64_t pseudo_random_prime_generator(int bits_size,primality_test_string){
	srand(time(NULL));
	int64_t range = pow(2,bits_size-1);
	int64_t num = range + rand()%(range);
	if(num%2==0)
		num++;
	while(primality_test(num,primality_test_string)==false){
		num+=2;
		if(num>=range*2)
			num = range + rand()%(range);
	}
	return num;
}

