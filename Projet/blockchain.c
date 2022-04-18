#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "listDeclaration.h"
#include "manipulationClefs.h"
#include "blockchain.h"


Block *creerBlock(Key *author, CellProtected *votes, unsigned char *hash, unsigned char *previous_hash, int nonce)  {
    // hyp: author a deja ete alloue
    Block *new = (Block *)malloc(sizeof(Block));

    //On s'assure de la bonne copie des hash en tant que unsigned char et pas char
    unsigned char *h = (unsigned char *)malloc((strlen((char *)hash)+1)*sizeof(unsigned char));
    unsigned char *ph = (unsigned char *)malloc((strlen((char *)previous_hash)+1)*sizeof(unsigned char));
    int i;
    for (i=0; i < strlen((char *)hash); i++)	{
        h[i] = hash[i];
    }
    h[i] = (unsigned char)'\0';
    for (i=0; i < strlen((char *)previous_hash); i++)     {
        ph[i] = previous_hash[i];
    }
    ph[i] = (unsigned char)'\0';

    new->author = author;
    new->votes = votes;
    new->hash = h;
    new->previous_hash = ph;
    new->nonce = nonce;
    return new;
}

void write_block(char *filename, Block *block)    {
    FILE *ostream = fopen(filename,"w");
    if (ostream == NULL)    {
        fprintf(stderr,"Erreur a l'ouverture du fichier %s en ecriture\n", filename);
        return;
    }
    char *author = key_to_str(block->author);
    
    //on écrit dans le fichier ostream les données du block
    fprintf(ostream,"%s %s %s %d\n",author, block->hash, block->previous_hash, block->nonce);
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
    //fprintf(stderr,"debut lireBlock\n");
    FILE *istream = fopen(filename,"r");
    if (istream == NULL)    {
        fprintf(stderr, "Erreur a l'ouverture du fichier %s en lecture\n", filename);
        return NULL;
    }
    char buffer[4096];
    char authorStr[256];
    unsigned char hash[256];
    unsigned char previous_hash[256];
    int nonce;

    //Lecture de la premiere ligne
    if (fgets(buffer,4096,istream) == NULL)  {
        fprintf(stderr,"Erreur a la lecture de la premiere ligne du ficher %s\n", filename);
        fclose(istream);
        return NULL;
    } else {
        if ( sscanf(buffer,"%s %s %s %d\n",authorStr,hash,previous_hash,&nonce) != 4)   {
            fprintf(stderr, "Erreur de formatage de la premiere ligne du fichier\n");
            fclose(istream);
            return NULL;
        } 
    }

    fprintf(stderr,"\nlire_block : %s\n",buffer);

    //Lecture des votes (on remet dans l'ordre des votes)
    CellProtected *votesTmp = NULL;
    while (fgets(buffer,4096,istream) != NULL)   {
        Protected *pr = str_to_protected(buffer);   //ne pas désallouer pr !
        add_protected(&votesTmp,pr);
    }
    CellProtected *votesTmpBis = votesTmp;
    CellProtected *votes = NULL;
    while (votesTmp)    {
        add_protected(&votes,votesTmp->data);
        votesTmp = votesTmp->next;
    }

    //On libere votesTmp, mais pas son contenu
    CellProtected *tmp;
    while (votesTmpBis) {
        tmp = votesTmpBis;
        votesTmpBis = votesTmpBis->next;
        free(tmp);
    }
    

    Block *b = creerBlock(str_to_key(authorStr),votes,hash,previous_hash,nonce);
    char *bStr = block_to_str(b);
    fprintf(stderr,"\nAffichage du bloc lu dans lire_block : %s\n", bStr);
    free(bStr);

    return b;
}

char *block_to_str(Block *block)    {
    //on prend un buffer assez grand pour tout stocker
    char buffer[4096];
    buffer[0] = '\0';
    char previous_hash[32];
    char nonce[32];

    //on obtient les informations et les concatene au buffer
    char *author = key_to_str(block->author);
    strcat(buffer,author);

    sprintf(previous_hash, " %s ", block->previous_hash);
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
    //on alloue avant de renvoyer avec strdup
    return strdup(buffer);
}

unsigned char* hash_function_block(const char* str){
    char *res = (char*)malloc(2*SHA256_DIGEST_LENGTH+1);
    char buffer[2*SHA256_DIGEST_LENGTH+1];
    unsigned char* d = SHA256( (const unsigned char*)str,strlen(str), 0);
    res[0]='\0';
    buffer[0]='\0';
    //on transforme la chaine en écriture héxadécimal
    for (int i=0; i<SHA256_DIGEST_LENGTH; i++){
        strcpy(buffer, res);
        sprintf(res,"%s%02x",buffer,d[i]);
        buffer[0] = '\0';   //on veut s'assurer que le contenu du buffer soit efface
    }
    return (unsigned char *)res;
}

int count_zeros(unsigned char* str){
    if (str == NULL){
        fprintf(stderr,"count_zero : str null");
        return -1;
    }
    int nbZeros = 0;
    int taille_str = strlen((const char*) str);
    //on compte le nombre de zéro d'affilé en tête de str
    while ( (nbZeros<taille_str) && (str[nbZeros]=='0') ){
        nbZeros++;
    }
    return nbZeros;
}

void compute_proof_of_work(Block *B, int d){
    B->nonce = 0;
    char *str = block_to_str(B);
    unsigned char* hash = hash_function_block((const char*) str);

    //tant qu'il n'y a pas d zéros en tête de hash, on incrémente nonce et on recalcule hash
    while (count_zeros(hash) < d ){
        free(str);
        free(hash);
        B->nonce ++;
        str = block_to_str(B);
        hash = hash_function_block((const char*) str);
    }
    free(str);
    free(B->hash);  //il faut liberer le hash qu'on a utilise pour initialiser le bloc avant de le remplacer
    B->hash = hash;
}

int verify_block(Block *B, int d)	{
    // Verifie que le nombre de zeros au debut du block hash est superieur ou  egal a d
    //TO DO : hashed ->memory leak?
    char *str = block_to_str(B);
    fprintf(stderr,"\naffichage verify_block : %s\n",str);
    unsigned char *hashed = hash_function_block(str);
    fprintf(stderr,"hashed : %s\n",hashed);
    int res = count_zeros(hashed) >= d;
    fprintf(stderr,"res = %d\n",res);
    free(hashed);
    free(str);
    return res;
}

void delete_block(Block *B)	{
    //Ne libere pas author, ni le contenu des cellules (Protected)
    if (!B)	{
        fprintf(stderr,"Error: delete_block, block null\n");
        return;
    }
    free(B->hash);
    free(B->previous_hash);
    CellProtected *curr = B->votes;
    CellProtected *tmp = NULL;
    while (curr) {
        tmp = curr;
        free(tmp);
        curr = curr->next;
    }
}
