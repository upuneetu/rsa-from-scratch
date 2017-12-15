#include "prime_helper.cpp"

bool naive_prime_tester(int64_t n);


bool naive_prime_tester(int64_t n){
	if(n%2==0)
		return false;

	for(int64_t i=1;(2*i+1)*(2*i+1)<=n;i++)
		if(n%(2*i+1)==0)
			return false;
	
	return true;
}

