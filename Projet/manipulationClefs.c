#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "outilsMathematiques.h"
#include "generationNbPremier.h"
#include "generationClef.h"
#include "testMillerRabin.h"
#include "rsa.h"
#include "manipulationClefs.h"

void init_key(Key *key, long val, long n)   {
    //ATTN: key->m correspond a key->val dans certains exemples (mais pas dans l'enonce qui l'a introduit!)
    key->m = val;
    key->n = n;
}

void init_pair_keys(Key *pKey, Key *sKey, long min_size, long max_size)   {
    assert(pKey != NULL && sKey != NULL);

    //Generation de deux nombres premiers differents
    long p = random_prime_number(min_size, max_size,5000);
    long q = random_prime_number(min_size, max_size,5000);
    while (p==q)    {
        q = random_prime_number(min_size,max_size,5000);
    }

    //generation des clefs
    long n,s,u;
    generate_key_values(p,q,&n,&s,&u);

    //Pour avoir des cles positives : 
    if (u<0) {
        
        long t = (p-1)*(q-1);
        u = u % t;
        u = u+t; //on aura toujours s*u mod t = 1
    }

    //Initialisation des cles
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}


char *key_to_str(Key *key)  {
    char buffer[256];
    sprintf(buffer, "(%lx,%lx)",key->m,key->n);
    return strdup(buffer);
}


Key *str_to_key(char *str)  {
    long m,n;
    sscanf(str,"(%lx,%lx)",&m,&n);
    Key *res = (Key *)malloc(sizeof(Key));
    init_key(res,m,n);
    return res;
}

Key *copie_key(Key *key)    {
    Key *new = (Key *)malloc(sizeof(Key));
    new->m = key->m;
    new->n = key->n;
    return new;
}