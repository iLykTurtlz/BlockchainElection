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
    *n = p*q;
    *s = rand_long(2,t-1);
    long v;
    long pgcd = extended_gcd(*s,t,u,&v);
    while(pgcd != 1)   {
        *s = rand_long(2,t-1);
        pgcd = extended_gcd(*s,t,u,&v);
    }    
    long test = (*s)*(*u) + t*v;
    if ( test != 1 )   {
        fprintf(stderr,"Erreur generate_key_values : %ld\n",test);
    }
}



