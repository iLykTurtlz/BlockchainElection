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
    key->m = val;
    key->n = n;
}

void init_pair_keys(Key *pKey, Key *sKey, long min_size, long max_size)   {
    assert(pKey != NULL && sKey != NULL);
    long p = random_prime_number(min_size, max_size,5000);
    long q = random_prime_number(min_size, max_size,5000);
    while (p==q)    {
        q = random_prime_number(min_size,max_size,5000);
    }
    long n,s,u;
    generate_key_values(p,q,&n,&s,&u);

    //Pour avoir des cles positives : 
    if (u<0) {
        
        long t = (p-1)*(q-1);
        u = u % t;
        u = u+t; //on aura toujours s*u mod t = 1
    }

    init_key(pKey, s, n);
    init_key(sKey, u, n);
    

}

char *key_to_str(Key *key)  {
    char buffer[256];
    sprintf(buffer, "(%lx,%lx)",key->m,key->n);
    return strdup(buffer);
    /*
    char *str = (char *)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(str,buffer);
    */
}

Key *str_to_key(char *str)  {
    long m,n;
    sscanf(str,"(%lx,%lx)",&m,&n);
    Key *res = (Key *)malloc(sizeof(Key));
    init_key(res,m,n);
    return res;
}






