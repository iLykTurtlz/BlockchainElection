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
    int res = !strcmp(mess,pr->mess);
    free(mess);
    return res;
}

char *protected_to_str(Protected *pr)    {
    char *res;
    char *keyStr = key_to_str(pr->pKey);
    char buffer[256];
    char *sgnStr = signature_to_str(pr->sgn);
    sprintf(buffer,"%s %s %s",keyStr, pr->mess, sgnStr);
    free(sgnStr);
    free(keyStr);
    res = strdup(buffer);
    return res;
}


Protected *str_to_protected(char *str)   {
    char keyStr[256];
    char mess[256];
    char sgn[256];
    if (sscanf(str, "%s %s %s", keyStr, mess, sgn) != 3)   {
        fprintf(stderr, "Erreur de lecture : str_to_protected\n");
        return NULL;
    } 
    Key *pKey = str_to_key(keyStr);
    Signature *signature = str_to_signature(sgn);
    return init_protected(pKey,mess,signature);
}

void freeProtected(Protected *pr)   {
    free(pr->pKey);
    free(pr->mess);
    freeSignature(pr->sgn);
    free(pr);
}






