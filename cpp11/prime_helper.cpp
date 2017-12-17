#include <inttypes.h>
#include <tuple>
#include <iostream>

int64_t gcd(int64_t n1,int64_t n2);
std::tuple<int64_t, int64_t, int64_t> x_gcd(int64_t n1,int64_t n2);
int64_t modular_inverse(int64_t a, int64_t n);
int64_t modular_exponentiation(int64_t a, int64_t p, int64_t n);
int jacobi_symbol(int64_t a, int64_t b);
int64_t pseudo_random_bit_generator(int bits_size);

int64_t gcd(int64_t n1,int64_t n2){

	int64_t temp;
	
	while(n1>0){
		temp = n1;
		n1 = n2 % n1;
		n2 = temp;
	}

	return n2;
}

std::tuple<int64_t, int64_t, int64_t> x_gcd(int64_t n1,int64_t n2){
	int64_t prev_x = 0, x = 1, prev_y = 1, y = 1;
	int64_t temp;
	while(n1>0){
		int64_t quotient = n2/n1;
		temp = x;
		x = prev_x - quotient * x;
		prev_x = temp;

		temp = y;
		y = prev_y - quotient * y;
		prev_y = y;

		temp = n1;
		n1 = n2 % n1;
		n2 = temp;
	}

	return std::make_tuple(prev_x, prev_y, n2);
}

int64_t modular_inverse(int64_t a, int64_t n){
	
	int64_t inv1,inv2,gcd;
	std::tie (inv1,inv2,gcd) = x_gcd(a,n);

	if(gcd>1)
		return 0;

	else
		return (inv1 + n) % n;

}

int64_t modular_exponentiation(int64_t a, int64_t p, int64_t n){
	int64_t accumulator = 1;
	a = a%n;
	while(p>0){

		if(p&1){
			accumulator = (accumulator * a)%n;
			p--;
		}
		
		a = (a * a)%n;
		p = p >> 1;
	}

	return accumulator%n;
}

int jacobi_symbol(int64_t a, int64_t b){
	
	if(b%2==0)
		return 0;

	int accumulator = 1;

	while(a!=0){

		while(a%2 == 0){
			a /= 2;
			if((b%8) == 5 || (b%8) == 3)
				accumulator *= -1;		
		}

		if(a<b){
			if( (a-1)%4 != 0 && (b-1)%4 != 0 )
				accumulator *= -1;
			int64_t temp = a;
			a = b ;
			b = temp;
		}

		a = a%b;
	}

	if(b==1)
		return accumulator;
	return 0;
}

/*int jacobi_symbol(int64_t a, int64_t b){

	if(b<=0 || b%2 == 0)
		return 0;
	int accumulator = 1;
	if(a<0){
		a *=-1;
		if(b%4==3)
			accumulator = -1;
	}

	while(a != 0){
		while(a%2 == 0) {
			a /= 2;
			if(b%8 == 3 || b%8 == 5)
				accumulator *= -1;
		}

		int64_t temp = b;
		b = a;
		a = temp;

		if(a%4 == 3 && b%4 == 3)
			accumulator *= 1;
		a = a%b;
	}

	if(b == 1)
		return accumulator;
	
		return 0;
}
*/

int64_t pseudo_random_prime_generator(int bits_size){
	srand(time(NULL));
	rand()%(pow(2,bits_size));
}