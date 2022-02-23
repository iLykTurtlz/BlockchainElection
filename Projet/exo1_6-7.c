#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long modpow_naive(long a, long m, long n)	{
	/* retourne a^m mod n, complexite O(m) = O(2^(log2(m)))*/
	long res=1;
	for (long i=0; i<m; i++)	{
		res = (res*a) % n;
	}
	return res;
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
        a = randlong(2, p-1);
        if (witness(a,b,d,p))   {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)	{
    if (argc != 2)  {
        fprintf(stderr,"usage : %s <val_max de m>\n",argv[0]);
        exit(1);
    }

    long MAX = atoi(argv[1]);
    long a = rand();
    long n = rand();

    clock_t temps_fin, temps_init;
    double tNaive, tOpti;

    FILE *stream = fopen("comparaisonExponentiationModulaire.txt","w");
    if (!stream)    {
        fprintf(stderr,"Erreur a l'ouverture du fichier\n");
    }

    fprintf(stream,"%20s %20s %20s\n","m","modpowNaive","modpow");

    for (long m=1; m<=MAX; m++) {
        temps_init = clock();
        modpow_naive(a,m,n);
        temps_fin = clock();
        tNaive = (double)(temps_fin - temps_init)/CLOCKS_PER_SEC;

        temps_init = clock();
        modpow(a,m,n);
        temps_fin = clock();
        tOpti = (double)(temps_fin - temps_init)/CLOCKS_PER_SEC;

        fprintf(stream,"%20ld %20f %20f\n",m,tNaive,tOpti);

    }

    fclose(stream);

    return 0;
}
