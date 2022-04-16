#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "outilsMathematiques.h"
#include "generationNbPremier.h"
#include "generationClef.h"
#include "testMillerRabin.h"


long extended_gcd(long s, long t, long *u, long *v) {
    //Algorithme d'Euclide
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
    *n = p * q;
    long t = (p-1) * (q-1);
    long v;
    *s = rand_long(0,t);
    while (extended_gcd( *s, t, u, &v ) != 1)   {
        *s = rand_long(0,t);
    }
}



