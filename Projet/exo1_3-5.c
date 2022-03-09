#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "outilsMathematiques.h"

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

    FILE *ostream = fopen("comparaisonExponentiationModulaire.txt","w");
    if (!ostream)    {
        fprintf(stderr,"Erreur a l'ouverture du fichier\n");
    }

    fprintf(ostream,"%20s %20s %20s\n","m","modpowNaive","modpow");

    for (long m=1; m<=MAX; m++) {
        temps_init = clock();
        modpow_naive(a,m,n);
        temps_fin = clock();
        tNaive = (double)(temps_fin - temps_init)/CLOCKS_PER_SEC;

        temps_init = clock();
        modpow(a,m,n);
        temps_fin = clock();
        tOpti = (double)(temps_fin - temps_init)/CLOCKS_PER_SEC;

        fprintf(ostream,"%20ld %20f %20f\n",m,tNaive,tOpti);

    }

    fclose(ostream);

    return 0;
}
