#include <stdio.h>
#include <time.h>
#include "outilsMathematiques.h"

int is_prime_naive(long p)	{
	/* Hyp : p impair.  Complexité O(p) n=log2p (le nb de bits pour stocker p), donc complexite O(2^n)*/
	if (p<2)	{
		return 0;
	}
	for (long i=3; i<(p/2); i+=2)	{
		if (p%i == 0){
			return 0;
		}
	}
	return 1;
}

long greatest_prime_under(double t)	{
	/* testable under t secondes */
	clock_t temps_init, temps_fin;
	double temps = 0;
	/*commencer par un nombre grand pour economiser du temps*/
	long p=219000001;
	//long p=3;
	long last_prime = 3;
	int is_prime=0;
	while (temps <= t)	{
		p+=2;
		temps_init = clock();
		is_prime = is_prime_naive(p);
		temps_fin = clock();
		temps = (double)(temps_fin-temps_init)/CLOCKS_PER_SEC;
		printf("%ld %f\n",p,temps);
		if (is_prime && temps < t)	{
			last_prime = p;
		}
	}
	return last_prime;
}

long modpow_naive(long a, long m, long n)	{
	/* retourne a^m mod n, complexite O(m) = O(2^(log2(m)))*/
	long res=1;
	for (int i=0; i<m; i++)	{
		res = (res*a) % n;
	}
	return res;
}

long modpow(long a, long m, long n)	{
	/* complexite O(log2(m))*/
	unsigned long res = 1;
	while (m > 0)	{
		if (m % 2 == 1)	{
			res = (res*a)%n;
		}
		a = (a*a) %n;
		m = m/2;
	}
	return res;
}

/*
int main()	{
	printf("%d\n",is_prime_naive(219000233));
	printf("%ld est le plus grand nombre premier qu'on peut tester en %d secondes\n",greatest_prime_under(2.),2);

	return 0; 
}
*/
 
