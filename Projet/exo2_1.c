#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int is_prime_naive(long p)	{
	/* Hyp : p impair.  Complexité O(p) n=log2p (le nb de bits pour stocker p), donc complexite O(2^n)*/
	if (p<2)	{
		return 0;
	}
	for (long i=3; i<p; i++)	{
		if (p%i == 0){
			return 0;
		}
	}
	return 1;
}


long modpow(long a, long m, long n)	{
	/* complexite O(log2(m))*/
	long res = 1;
	while (m > 0)	{
		if (m % 2 == 1)	{
			res = (res*a)%n;
		}
		a = (a*a) %n;
		m = m/2;
	}
	return res;
}

int witness(long a, long b, long d, long p) {
    long x = modpow(a,d,p);
    if (x == 1) {
        return 0;
    }
    for (long i=0; i<b; i++)    {
        if (x == p-1)   {
            return 0;
        }
        x = modpow(x,2,p);
    }
    return 1;
}

long rand_long(long low, long up)  {
    return rand() % (up - low + 1) + low;
}

int is_prime_miller(long p, int k)  {
    if (p == 2) {
        return 1;
    }
    if (!(p & 1) || (p <= 1))   { //on verifie que p est impair et different de 1
        return 0;
    }
    //on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!(d & 1))    { // tant que d n'est pas impair
        d = d/2;
        b = b + 1;
    }
    // On genere k valeurs pour a, et on teste si c'est un temoin
    long a;
    int i;
    for (i=0; i<k; i++) {
        a = rand_long(2, p-1);
        if (witness(a,b,d,p))   {
            return 0;
        }
    }
    return 1;
}

long random_prime_number(int min_size, int max_size, int k)  {
    long p = pow(2,min_size);
    long max_p = pow(2,(max_size+1));
    while (p < max_p)   {
        if (is_prime_miller(p,k))   {
            return p;
        }
        p++;
    }
    return -1;  //cas d'echec
}

long extended_gcd(long s, long t, long *u, long *v) {
    if (t==0)   {
        *u = 1;
        *v = 0;
        return s;
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t, s%t, &uPrim, &vPrim);
    *u = vPrim;
    *v = uPrim - (s/t)*vPrim;
    return gcd;
}

void generate_key_values(long p, long q, long *n, long *s, long *u) {
    
}