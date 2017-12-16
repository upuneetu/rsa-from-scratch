#include "prime_helper.cpp"
#include <set>
#include <ctime>
#include <cstdlib>
bool naive_primality_test(int64_t n);


bool naive_primality_test(int64_t n){
	if(n%2==0)
		return false;

	for(int64_t i=1;(2*i+1)*(2*i+1)<=n;i++)
		if(n%(2*i+1)==0)
			return false;
	
	return true;
}

bool fermats_primality_test(int64_t n,int64_t k=10){
	if(n%2==0)
		return false;

	std::set<int64_t> checked_elements;
	srand(time(NULL));
	while(k>0) {
		int64_t a = rand()%n;
		if(gcd(a,n)!=0)
			return false;
		else if(checked_elements.find(a)!=std::set::end)
			continue;
		if(modular_exponentiation(a,n-1,n)!=1)
			return false;
		set.insert(a);
		k--;		
	}

	return true;
}

