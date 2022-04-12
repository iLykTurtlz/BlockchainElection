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

Signature *init_signature(long *content, int size)  {
    Signature *res = (Signature *)malloc(sizeof(Signature));
    res->content = content;
    res->size = size;
    return res;
}

Signature *sign(char *mess, Key *sKey)  {
    long *sgn = encrypt(mess, sKey->m, sKey->n);
    return init_signature(sgn,strlen(mess));
}

char *signature_to_str(Signature *sgn)  {
    char *result = malloc(10*sgn->size*sizeof(char));
    result[0] = '#';
    int pos = 1;
    char buffer[256];
    for (int i=0; i<sgn->size; i++) {
        sprintf(buffer, "%lx", sgn->content[i]);
        for (int j=0; j<strlen(buffer); j++)    {
            result[pos] = buffer[j];
            pos = pos+1;
        }
        result[pos] = '#';
        pos = pos+1; 
    }
    result[pos] = '\0';
    result = realloc(result, (pos+1)*sizeof(char));
    return result;
}

Signature *str_to_signature(char *str)  {
    int len = strlen(str);
    long *content = (long *)malloc(sizeof(long)*len);
    int num = 0;
    char buffer[256];
    int pos = 0;
    for (int i=0; i<len; i++)   {
        if (str[i] != '#')  {
            buffer[pos] = str[i];
            pos = pos+1;
        } else{
            if (pos != 0)   {
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num = num+1;
                pos = 0;
            }
        }
    }
    content = realloc(content, num*sizeof(long));
    return init_signature(content, num);
}

void freeSignature(Signature *s)    {
    free(s->content);
    free(s);
}





