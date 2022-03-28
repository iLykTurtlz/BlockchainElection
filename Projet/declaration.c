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
#include "signature.h"
#include "declaration.h"

Protected *init_protected(Key *pKey, char *mess, Signature *sgn)    {
    Protected *res = (Protected *)malloc(sizeof(Protected));
    res->pKey = pKey;
    res->mess = strdup(mess);
    res->sgn = sgn;
    return res;
}

int verify(Protected *pr)   {
    char *mess = decrypt(pr->sgn->content,pr->sgn->size,pr->pKey->m, pr->pKey->n);
    return !strcmp(mess,pr->mess);
}

char *protected_to_str(Protected *pr)    {
    char *res;
    char buffer[256];
    char *sgn = signature_to_str(pr->sgn);
    sprintf(buffer,"%lx %lx %s %s",pr->pKey->m, pr->pKey->n, pr->mess, sgn);
    free(sgn);
    res = strdup(buffer);
    return res;
}


Protected *str_to_protected()   {


}





