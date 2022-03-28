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

#endif