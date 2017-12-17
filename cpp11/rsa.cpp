#include "primality_tests.cpp"
#include "prime_helper.cpp"
#include <cmath>
#include <utility>

int64_t pseudo_random_prime_generator(int bits_size);
class RSA{
private:
	std::string primality_test;
	int bits_size;
	int64_t p,q;
	int64_t n,phi;
	int64_t private_key,public_key;

	void generate_and_assign_keys();
public:
	RSA(int bits_size,std::string primality_test_string){
		this->bits_size = bits_size;
		this->primality_test.assign(primality_test_string);
		
		this->p = pseudo_random_prime_generator(bits_size,primality_test_string);
		this->q = pseudo_random_prime_generator(bits_size,primality_test_string);

		this->n = p*q;
		this->phi = (p-1)*(q-1);

		generate_and_assign_keys();

	}
	
}

void RSA::generate_and_assign_keys(){
	srand(time(NULL));
	int64_t n = rand()%(this->phi-2)+1;
	while(gcd(n,this->phi)!=1){
		n = rand()%(this->phi-2)+1;
	}
	this->public_key = n;
	this->private_key = modular_inverse(n,this->phi);
}

//change this prime generator, very insecure primes are generated here
int64_t pseudo_random_prime_generator(int bits_size,std::primality_test_string){
	srand(time(NULL));
	int64_t num = rand()%(pow(2,bits_size));
	while(primality_test(num,primality_test_string)==false){
		num = rand()%(pow(2,bits_size));
	}
	return num;
}

