
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "outilsMathematiques.h"
#include "testMillerRabin.h"



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
        k = 1; //rand_long(1,MAX_K);
        int pm = is_prime_miller(p,k);
        printf("is_prime_miller(%ld, %ld) = %d\n",p,k,pm);
        if (pm != is_prime_naive(p))  {
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

