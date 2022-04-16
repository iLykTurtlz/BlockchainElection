#ifndef DECLARATION_H
#define DECLARATION_H

#include "signature.h"
#include "manipulationClefs.h"

typedef struct {
    Key *pKey;
    char *mess;
    Signature *sgn;
} Protected;

Protected *init_protected(Key *pKey, char *mess, Signature *sgn);
int verify(Protected *pr);
char *protected_to_str(Protected *pr);
Protected *str_to_protected(char *str);

#endif