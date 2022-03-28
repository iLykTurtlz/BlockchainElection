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
    
    fprintf(keyFile, "%20s %20s\n","cle publique","cle privee");
    //Generation de nv couples cles.
    Key keys[2*nv];


    Key *public = (Key *)malloc(sizeof(Key));
    Key *private = (Key *)malloc(sizeof(Key));
    char publicString[256];
    char privateString[256]; 

    int nbKeys = 0;
    int i, unique;
    while (nbKeys < nv)  {
        unique = 1;
        init_pair_keys(public, private, 3, 7);
        strcpy(publicString, key_to_str(public));
        strcpy(privateString, key_to_str(private));
        for (i=0; i<nbKeys && unique; i++)    {
            if (strcmp(publicString, key_to_str(&keys[i])) || strcmp(privateString, key_to_str(&keys[i])))    {
                unique = 0;
            }
        }
        if (unique) {
            keys[nbKeys++] = *public;
            keys[nbKeys++] = *private;
            fprintf(keyFile,"%20s %20s\n",publicString,privateString);
        }
        fprintf(stderr,"loop\n");
    }
    fclose(keyFile);

    //Generation fichier candidats, candidates.txt
    Key candidateKeys[nc];
    srand(time(NULL));

    int indice;
    for (int j=0; j<nc; j++)    {
        indice = (rand() % nv)*2;
        candidateKeys[j] = keys[indice];
        fprintf(candidateFile,"%s\n",key_to_str(&candidateKeys[j]));
    }
    fclose(candidateFile);

    //Generation de declarations de vote aleatoires, declarations.txt
    char mess[256];
    for (int k=0; k<nv; k++)    {
        Protected *pr;
        indice = rand() % nc;
        strcpy(mess,key_to_str(&candidateKeys[indice]));
        pr = init_protected(&keys[2*k], mess, sign(mess,&keys[2*k+1]));
        fprintf(declarationFile,"%s\n",protected_to_str(pr));
        free(pr);
    }
    fclose(declarationFile);
    return;
}

