#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "manipulationClefs.h"
#include "declaration.h"
#include "signature.h"


void generate_random_data(int nv, int nc) {
    /* Hyp : nc <= nv */
    FILE *keyFile = fopen("keys.txt","w");
    FILE *candidateFile = fopen("candidates.txt","w");
    FILE *declarationFile = fopen("declarations.txt","w");

    if (!keyFile || !candidateFile || !declarationFile) {
        fprintf(stderr,"Erreur : generate_random_data, ouverture de fichier\n");
        return;
    }
    
    
    
    //Generation de nv couples cles.
    
    Key *pKeys[nv];
    Key *sKeys[nv];

    int i = 0;  
    while (i < nv)  {
        Key *public = (Key *)malloc(sizeof(Key));
        Key *private = (Key *)malloc(sizeof(Key));
        init_pair_keys(public, private, 3, 7);
        char *publicString = key_to_str(public);
        char *privateString = key_to_str(private);

        pKeys[i] = public;
        sKeys[i] = private;
        //ecriture dans keys.txt
        fprintf(keyFile,"%s %s\n",publicString,privateString);
        //fprintf(stderr,"%lx %lx\n", public->m, public->n);
        
        free(publicString);
        free(privateString);
        i++;
    }
    fclose(keyFile);

    //Generation fichier candidats, candidates.txt
    Key *candidateKeys[nc];

    int cIndices[nc];
    for (int i=0; i<nc; i++)    {
        cIndices[i] = -1;
    }
    int j=0, indice, unique;
    while (j<nc)    {
        unique = 1;
        indice = rand() % nv;
        for (int k=0; k<=j; k++) {
            
            if (cIndices[k] == indice)  {
                unique = 0;
                break;
            }
        }
        
        if (unique == 1) {
            candidateKeys[j] = pKeys[indice];
            cIndices[j] = indice;
            fprintf(candidateFile,"%s\n",key_to_str(candidateKeys[j]));
            j++;
        }
    }
    
    fclose(candidateFile);
    

    //Generation de declarations de vote aleatoires, declarations.txt
    
    for (int k=0; k<nv; k++)    {
        Protected *pr;
        indice = rand() % nc;
        char *mess = key_to_str(candidateKeys[indice]);
        pr = init_protected(pKeys[k], mess, sign(mess,sKeys[k]));
        char *prString = protected_to_str(pr);
        fprintf(declarationFile,"%s\n",prString);
        free(prString);
        free(mess);
        free(pr->mess);
        free(pr->sgn);
    }
    for (int l=0; l<nv; l++)    {
        free(pKeys[l]);
        free(sKeys[l]);
    }
    
    fclose(declarationFile);

    return;
}

