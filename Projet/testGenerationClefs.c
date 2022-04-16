#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manipulationClefs.h"
#include "generationClef.h"
#include "testMillerRabin.h"
#include "generationNbPremier.h"
#include "outilsMathematiques.h"




int main()  {
    srand(time(NULL));
    int min_size = 3;
    int max_size = 7;

    for (int i=0; i<10; i++)    {
        long p,q,n,s,u;

        p = random_prime_number(min_size, max_size,5000);
        q = random_prime_number(min_size, max_size,5000);
        while (p==-1)   {
            p = random_prime_number(min_size, max_size,5000);
        }
        while (p==q || q == -1)    {
            q = random_prime_number(min_size,max_size,5000);
        }
        generate_key_values(p,q,&n,&s,&u);

        fprintf(stderr,"Premier essai:\n");
        fprintf(stderr,"(s,n) = (%ld,%ld) \t (u,n) = (%ld,%ld)\n",s,n,u,n);

        //pour avoir u positif
        if (u<0) {
            long t = (p-1)*(q-1);
            u = u+t; //on aura toujours s*u mod t = 1
            fprintf(stderr,"Deuxieme essai:\n");
            fprintf(stderr,"(s,n) = (%ld,%ld) \t (u,n) = (%ld,%ld)\n",s,n,u,n);
        }
    }

    return 0;
}