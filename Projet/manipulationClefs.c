#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "outilsMathematiques.h"
#include "generationNbPremier.h"
#include "generationClef.h"
#include "testMillerRabin.h"
#include "rsa.h"
#include "manipulationClefs.h"

void init_key(Key *key, long val, long n)   {
    key->s = val;
    key->n = n;
}

void init_pair_keys(Key *pkey, Key *skey, long min_size, long max_size)   {
    long p = random_prime_number(min_size, max_size,k);
    long q = random_prime_number(min_size, max_size,k);

}

