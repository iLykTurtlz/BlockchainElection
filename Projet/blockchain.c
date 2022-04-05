#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listDeclaration.h"
#include "manipulationClefs.h"
#include "blockchain.h"




Block *creerBlock(Key *author, CellProtected *votes, unsigned char hash, unsigned char previous_hash, int nonce)  {
    // hyp: author a deja ete alloue
    Block *new = (Block *)malloc(sizeof(Block));
    new->author = author;
    new->votes = votes;
    new->hash = hash;
    new->previous_hash = previous_hash;
    new->nonce = nonce;
    return new;
}

void enregistrerBlock(char *filename, Block *block)    {
    FILE *ostream = fopen(filename,"w");
    if (ostream == NULL)    {
        fprintf("Erreur a l'ouverture du fichier %s en ecriture\n", filename);
        return;
    }
    char *author = key_to_str(block->author);
    fprintf(ostream,"%s %hhu %hhu %d\n",block->author, block->hash, block->previous_hash, block->nonce);
    CellProtected *voteList = block->votes;
    while (voteList) {
        char *str = protected_to_str(voteList->data);
        fprintf(ostream, "%s\n",str);
        voteList = voteList->next;
        free(str);
    }
    free(author);
    fclose(ostream);
}

Block *lireBlock(char *filename)    {
    FILE *istream = fopen(filename,"r");
    if (istream == NULL)    {
        fprintf("Erreur a l'ouverture du fichier %s en lecture\n", filename);
        return;
    }

    char buffer[256];
    char authorStr[256];
    unsigned char hash;
    unsigned char previous_hash;
    int nonce;

    //Lecture de la premiere ligne
    if (fgets(buffer,256,istream) == NULL)  {
        fprintf(stderr,"Erreur a la lecture de la premiere ligne du ficher %s\n", filename);
        fclose(istream);
        return NULL;
    } else {

        if ( sscanf(buffer,"%s %hhu %hhu %d\n",authorStr,&hash,&previous_hash,&nonce) != 4)   {
            fprintf(stderr, "Erreur de formatage de la premiere ligne du fichier\n");
            fclose(istream);
            return NULL;
        } 
    }

    //Lecture des votes
    CellProtected *votes = NULL;
    while (fgets(buffer,256,istream) != NULL)   {
        Protected *pr = str_to_protected(buffer);
        add_protected(&votes,pr);
    }
    return creerBlock(str_to_key(authorStr),votes,hash,previous_hash,nonce);
}

char *block_to_str(Block *block)    {
    char *res;
    char buffer[512];
    buffer[0] = '\0';
    char previous_hash[8];
    char nonce[8];

    //on obtient les informations et les concatene au buffer
    char *author = key_to_str(block->author);
    strcat(buffer,author);

    sprintf(previous_hash, " %hhu ", block->previous_hash);
    strcat(buffer,previous_hash);

    CellProtected *votes = block->votes;
    while (votes)   {
        char *prStr = protected_to_str(votes->data);
        strcat(buffer,prStr);
        strcat(buffer, " ");
        free(prStr);
        votes = votes->next;
    }

    sprintf(nonce, "%d", block->nonce);
    strcat(buffer,nonce);

    free(author);
    return strdup(buffer);
}





