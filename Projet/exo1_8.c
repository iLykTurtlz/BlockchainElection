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

int main(int argc, char **argv)	{
    
    if (argc != 4)  {
        fprintf(stderr,"usage : %s <val_de_k> <min_size> <max_size>\n",argv[0]);
        exit(1);
    }



    int k = atoi(argv[1]);
    int min_size = atoi(argv[2]);
    int max_size = atoi(argv[3]);

    if (min_size < 0 || max_size > 32)  {
        fprintf(stderr,"usage : min et max entre 0 et 32\n");
        exit(1);
    }

    printf("Generation d'un nombre premier de taille comprise entre %d et %d : %ld\n",min_size, max_size, random_prime_number(min_size,max_size,k));
   



 
    return 0;
}
