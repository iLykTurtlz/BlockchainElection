#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "outilsMathematiques.h"
#include "testMillerRabin.h"
#include "generationNbPremier.h"




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

/*
int main(int argc, char **argv)	{
    
    if (argc != 4)  {
        fprintf(stderr,"usage : %s <val_de_k> <min_size> <max_size>\n",argv[0]);
        exit(1);
    }



    int k = atoi(argv[1]);
    int min_size = atoi(argv[2]);
    int max_size = atoi(argv[3]);

    if (min_size < 0 || max_size > 32 || min_size > max_size)  {
        fprintf(stderr,"usage : min et max entre 0 et 32 avec min <= max\n \n");
        exit(1);
    }
    printf("Generation d'un nombre premier de taille comprise entre %d et %d : %ld\n",min_size, max_size, random_prime_number(min_size,max_size,k));

    return 0;
}

*/
