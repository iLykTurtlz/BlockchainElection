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
    
    fprintf(keyFile, "%-20s %-20s\n","cle publique","cle privee");
    
    
    //Generation de nv couples cles.
    
    Key *pKeys[nv];
    Key *sKeys[nv];
    int unique;
    int i = 0;  
    while (i < nv)  {
        printf("i = %d, nv = %d\n",i,nv);
        unique = 1;
        Key *public = (Key *)malloc(sizeof(Key));
        Key *private = (Key *)malloc(sizeof(Key));
        init_pair_keys(public, private, 3, 7);
        char *publicString = key_to_str(public);
        char *privateString = key_to_str(private);

/*
        printf("avant boucle for\n");

        
        for (int j=0; j<i; j++) {

            char *pk = key_to_str(pKeys[j]);
            char *sk = key_to_str(sKeys[j]);
            if ( strcmp(publicString,pk) || strcmp(privateString, sk) )   {
                printf("modification unique\n");
                unique = 0;
                break;
            }
            free(pk);
            free(sk);
        }
        printf("fin boucle for\n");
        */
        if (unique) {
            pKeys[i] = public;
            sKeys[i] = private;
            //ecriture dans keys.txt
            fprintf(keyFile,"%-20s %-20s\n",publicString,privateString);
            printf("i++\n");
            i++;
        }

        free(publicString);
        free(privateString);
    }
    fclose(keyFile);

    //Generation fichier candidats, candidates.txt
    Key *candidateKeys[nc];
    srand(time(NULL));

    int indice;
    for (int j=0; j<nc; j++)    {
        indice = rand() % nv;
        candidateKeys[j] = pKeys[indice];
        fprintf(candidateFile,"%s\n",key_to_str(candidateKeys[j]));
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

