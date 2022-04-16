#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "outilsMathematiques.h"
#include "testMillerRabin.h"
#include "generationNbPremier.h"




long random_prime_number(int min_size, int max_size, int k)  {
    long min_p = pow(2,(min_size));
    long max_p = pow(2,(max_size-1));
    long p = rand_long(min_p, max_p);

    //On trouve un nombre premier aleatoire
    while (!is_prime_miller(p,k))   {
        p = rand_long(min_p, max_p);
    }
    return p;
}
