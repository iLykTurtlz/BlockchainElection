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

    int nbCles = 0;  
    while (nbCles < nv)  {
        Key *public = (Key *)malloc(sizeof(Key));
        Key *private = (Key *)malloc(sizeof(Key));
        init_pair_keys(public, private, 3, 7);
        char *publicString = key_to_str(public);
        char *privateString = key_to_str(private);

        pKeys[nbCles] = public;
        sKeys[nbCles] = private;

        //ecriture dans keys.txt
        fprintf(keyFile,"%s %s\n",publicString,privateString);
        
        free(publicString);
        free(privateString);
        nbCles++;
    }
    fclose(keyFile);


    //Generation fichier candidats, candidates.txt
    Key *candidateKeys[nc];
    int cIndices[nc];

    //On stocke les indices des cles publiques qui sont aussi candidats
    for (int i=0; i<nc; i++)    {
        cIndices[i] = -1;
    }

    int nbCand=0, indice, unique;
    char *candStr;
    while (nbCand < nc)    {
        unique = 1;
        indice = rand() % nv;
        //on verifie si le candidat existe deja
        for (int k=0; k<=nbCand; k++) {
            if (cIndices[k] == indice)  {
                unique = 0;
                break;
            }
        }
        //on ajoute le nouveau candidat dans la liste et dans le fichier
        if (unique == 1) {
            candidateKeys[nbCand] = pKeys[indice];
            cIndices[nbCand] = indice;
            candStr = key_to_str(candidateKeys[nbCand]);
            fprintf(candidateFile,"%s\n",candStr);
            free(candStr);
            nbCand++;
        }
    }
    fclose(candidateFile);
    

    //Generation de declarations de vote aleatoires, declarations.txt
    for (int k=0; k<nv; k++)    {
        Protected *pr;
        indice = rand() % nc;

        char *mess = key_to_str(candidateKeys[indice]);
        pr = init_protected(pKeys[k], mess, sign(mess,sKeys[k]));
        char *prStr = protected_to_str(pr);
        //Ecriture de la declaration dans le fichier
        fprintf(declarationFile,"%s\n",prStr);

        free(prStr);
        free(mess);
        freeSignature(pr->sgn);	//ne pas liberer la pr->pKey, qui est dans le tableau
	free(pr->mess);
	free(pr);
    }
    fclose(declarationFile);
    
    for (int l=0; l<nv; l++)    {
        free(pKeys[l]);
        free(sKeys[l]);
    }
}

