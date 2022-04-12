#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manipulationClefs.h"
#include "generationClef.h"



int main()  {
    srand(time(NULL));

    for (int i=0; i<10; i++)    {
        long p,q,*n, long *s, long *u
        long p,q,n,s,u;

        p = random_prime_number(min_size, max_size,5000);
        q = random_prime_number(min_size, max_size,5000);
        while (p==q)    {
            q = random_prime_number(min_size,max_size,5000);
        }
        fprintf(stderr,"Premier essai:\n");
        fprintf(stderr,"(s,n) = (%ld,%ld) \t (u,n) = (%ld,%ld)\n",s,n,u,n);

        if (u<0) {
            long t = (p-1)*(q-1);
            u = u+t; //on aura toujours s*u mod t = 1
            fprintf(stderr,"Deuxieme essai:\n");
            fprintf(stderr,"(s,n) = (%ld,%ld) \t (u,n) = (%ld,%ld)\n",s,n,u,n);
        }
    }

    return 0;
}