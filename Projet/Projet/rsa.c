#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "outilsMathematiques.h"
#include "generationNbPremier.h"
#include "generationClef.h"
#include "testMillerRabin.h"
#include "generationClef.h"
#include "string.h"

long *encrypt(char *chaine, long s, long n) {
    int size = strlen(chaine);
    long *msg = (long *)malloc((size)*sizeof(long));
    int i;
    for (i=0; i<size; i++)  {
        msg[i] = modpow((int)chaine[i],s,n);
    }
    return msg;
}

char *decrypt(long *encrypted, int size, long u, long n)    {
    char *msg = (char *)malloc((size+1)*sizeof(char));
    int i;
    for (i=0; i<size; i++)  {
        msg[i] = modpow(encrypted[i],u,n);
    }
    msg[i] = '\0';
    return msg;
}