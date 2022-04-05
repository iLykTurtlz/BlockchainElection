#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "outilsMathematiques.h"
#include "generationNbPremier.h"
#include "generationClef.h"
#include "testMillerRabin.h"


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
    long t = (p-1)*(q-1);
    fprintf(stderr,"(p-1) = %ld \t (q-1) = %ld \t (p-1)*(q-1) = %ld\n",p-1,q-1,t);
    *n = p*q;
    fprintf(stderr,"n = p*q = %ld \t ",*n);
    *s = rand_long(2,t-1);
    fprintf(stderr,"s = %ld\n", *s);
    long v;
    long pgcd = extended_gcd(*s,t,u,&v);
    fprintf(stderr,"\n(s,t,u,v) = (%ld,%ld,%ld,%ld)\n",*s,t,*u,v);
    fprintf(stderr,"pgcd = extended_gcd(s,t,u,v) = %ld\n",pgcd);
    while(pgcd != 1)   {
        *s = rand_long(2,t-1);
        pgcd = extended_gcd(*s,t,u,&v);
        fprintf(stderr,"TOUR\n");
        fprintf(stderr,"(s,t,u,v) = (%ld,%ld,%ld,%ld)\n",*s,t,*u,v);
        fprintf(stderr,"pgcd = extended_gcd(s,t,u,v) = %ld\n",pgcd);
    }    
    long test = (*s)*(*u) + t*v;
    if ( test != 1 )   {
        fprintf(stderr,"Erreur generate_key_values : %ld\n",test);
    }
}



