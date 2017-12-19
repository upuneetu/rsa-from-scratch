#include "prime_helper.cpp"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>

bool naive_primality_test(int64_t n);
bool fermats_primality_test(int64_t n,int64_t k);
bool solvay_strassen_primality_test(int64_t n,int64_t k);
bool miller_rabin_primality_test(int64_t n, int64_t k);
bool primality_test(int64_t n,std::string primality_test_string);

bool naive_primality_test(int64_t n){
	if(n%2==0)
		return false;

	for(int64_t i=1;(2*i+1)*(2*i+1)<=n;i++)
		if(n%(2*i+1)==0)
			return false;
	
	return true;
}

bool fermats_primality_test(int64_t n,int64_t k=10){
	if(n==2)
		return true;
	if(n%2==0)
		return false;

	
	srand(time(NULL));
	while(k>0) {
		int64_t a = rand()%(n-3)+2;
		if(gcd(a,n)!=1||modular_exponentiation(a,n-1,n)!=1)
			return false;	
		k--;		
	}

	return true;
}

bool solvay_strassen_primality_test(int64_t n,int64_t k=10){
	if(n==2)
		return true;
	if(n%2==0||n==1)
		return false;

	srand(time(NULL));
	while(k>0) {
		
		int64_t a = rand()%(n-2)+1;
		if((jacobi_symbol(a,n)+n)%n!=modular_exponentiation(a,(n-1)/2,n))
			return false;
		
		k--;
	}

	return true;
}

bool miller_rabin_primality_test(int64_t n, int64_t k=10){

	int64_t s = 0,d=n-1;
	bool witness_flag;
	while(d%2==0){
		d = d >> 1;
		s++;
	}
	
	while(k){
		k--;
		int64_t p = s;
		int64_t a = rand()%(n-2)+1;
		if(modular_exponentiation(a,d,n)==1)
			continue;
		witness_flag = 1;
		s--;
		while(s>=0){
			if(modular_exponentiation(a,(pow(2,s)*d),n)==n-1){
				witness_flag = 0;
				break;
			}
			s--;
		}

		if(witness_flag)
			return false;
		s = p;
	}

	return true;
}


bool primality_test(int64_t n,std::string primality_test_string){
	if(primality_test_string.compare("solvay_strassen"))
		return solvay_strassen_primality_test(n);
	if(primality_test_string.compare("miller_rabin"))
		return miller_rabin_primality_test(n);
}
