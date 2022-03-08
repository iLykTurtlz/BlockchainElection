#include <stdio.h>
#include <stdlib.h>



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
        a = rand_long(2, p-1);
        if (witness(a,b,d,p))   {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)	{
    
    if (argc != 3)  {
        fprintf(stderr,"usage : %s <val_max_de_k> <nb_essais>\n",argv[0]);
        exit(1);
    }

    long p,k;
    int MAX_K = atoi(argv[1]);
    int nb_essais = atoi(argv[2]);
    int echecs=0;



    //clock_t temps_fin, temps_init;

    FILE *ostream = fopen("fiabiliteTestMillerRabin.txt","w");
    if (!ostream)    {
        fprintf(stderr,"Erreur a l'ouverture du fichier\n");
        exit(1);
    }

    fprintf(ostream,"%20s %20s\n","p","erreur?");

 
    

    for (long i=0; i<=nb_essais; i++) {
        p = rand_long(2,2147483647);
        k = rand_long(1,MAX_K);
        if (is_prime_miller(p,k) != is_prime_naive(p))  {
            fprintf(ostream,"%20ld %20s\n",p,"erreur");
            echecs++;
        } else {
            fprintf(ostream,"%20ld %20s\n",p,"pas d'erreur");
        }
    }
    fprintf(ostream,"Prob d'erreur du test Miller : ");
    fprintf(ostream,"%20f\n",((double)(echecs))/((double)(nb_essais)));

    fclose(ostream);
    return 0;
}
