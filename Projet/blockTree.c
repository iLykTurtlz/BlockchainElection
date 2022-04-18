#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include "blockchain.h"
#include "blockTree.h"
#include "winner.h"
#include "listKey.h"

CellTree *create_node(Block *b) {
    CellTree *new = (CellTree *)malloc(sizeof(CellTree));
    new->block = b;
    new->father = NULL;
    new->firstChild = NULL;
    new->nextBro = NULL;
    new->height = 0;
    return new;
}

int update_height(CellTree *father, CellTree *child)    {
    
    if ((father == NULL)||(child == NULL))  {
        fprintf(stderr,"Error : update_height, father or child null\n");
    }
    if (child->father != father)	{
        fprintf(stderr,"Error: update_height, You are NOT the father\n");
    }
    if (father->height < child->height+1){
        father->height = child->height+1;
        return 1;
    }else {
        //on ne modifie pas le père
        return 0;
    }
}

void add_child(CellTree *father, CellTree *child)   {
    if (child == NULL || father == NULL)  {
        fprintf(stderr,"Error : add_child : child or father null\n");
        return;
    }
    //On actualise le previous hash de child
    if ( strcmp((char *)child->block->previous_hash, (char *)father->block->hash) != 0 ) {
        fprintf(stderr,"Erreur : add_child, you are not HIS child!\n");
        return;
    }

    //on actualise le pere de child
    child->father = father;
    
    //on ajoute le fils
    CellTree *curr = father->firstChild;
    if (curr == NULL)   {
        father->firstChild = child;
    }else{
        //on cherche le dernier des frères du fils du père
        while (curr->nextBro)   {
            curr = curr->nextBro;
        }
        curr->nextBro = child;
    }

    //on met à jour la hauteur des pères tant qu'il y a des modifications
    CellTree *fathers = father;
    CellTree *children = child;
    int modification = 1;
    while ((fathers)&&(modification==1))    {
        modification = update_height(fathers,children);
        children = fathers;
        fathers = fathers->father;
    }  
}

void print_tree(CellTree *tree) {
    if (!tree)  {
        return;
    }
    //on affiche le noeud courrant
    printf("Block de hauteur : %d, et d'identifiant : %s\n", tree->height, tree->block->hash);
    
    //on appelle la fonction pour ses frères puis ses fils
    if (tree->nextBro){
        print_tree(tree->nextBro);
    }
    if (tree->firstChild){
        print_tree(tree->firstChild);
    }
}

void delete_node(CellTree *node)    {
    delete_block(node->block);
    free(node);
}

void delete_tree(CellTree *tree){
    if (tree){
        CellTree *brothers = tree->nextBro;
        CellTree *children =  tree->firstChild;

        //on supprime le noeud courant 
        delete_node(tree);

        //on supprime ses frères puis ses fils
        delete_tree(brothers);
        delete_tree(children);
    }
}

CellTree* highest_child(CellTree* cell){
    //retourne l'adresse du fils dont la hauteur est la plus grande
    if (cell==NULL)  {
        fprintf(stderr,"Error : highest_child : cell null\n");
        return NULL;
    }
    CellTree* child = cell->firstChild;
    CellTree* highest_child = cell->firstChild;
    while(child){
        if (child->height > highest_child->height){
            highest_child = child;
        }
        child = child->nextBro;
    }
    return highest_child;
} 

CellTree *last_node(CellTree *tree) {
    //Retourne la feuille de la plus longue branche
    if (tree == NULL)   {
        return NULL;
    }
    //renvoie une feuille
    if (tree->firstChild == NULL)   {
        return tree;
    //parcourt le plus grand fils    
    } else {
        return last_node(highest_child(tree));
    }
}

//Version qui utilise last_node
CellProtected *votesBrancheMax(CellTree *tree)   {
    //on fusionne les listes de votes de la plus longue branche
    if (tree == NULL)   {
        fprintf(stderr, "Erreur : votesBrancheMax, tree NULL\n");
        return NULL;
    }
    CellTree *node = last_node(tree);
    CellProtected *res = NULL;
    while (node != NULL)    {
        res = fusionner_list_protected(res, copie_list_protected(node->block->votes));
        node = node->father;
    }
    return res;
}
/*
//Version qui utilise highest_child
CellProtected *votesBrancheMax(CellTree *tree)  {
    //on fusionne les listes de votes de la plus longue branche
    if (tree == NULL)   {
        fprintf(stderr, "Erreur : votesBrancheMax, tree NULL\n");
        return;
    }
    //renvoie une feuille
    if (tree->firstChild == NULL)   {
        return copie_list_protected(tree->block->votes);
    //parcourt le plus grand fils    
    } else {
        return fusionner_list_protected(copie_list_protected(tree->block->votes),votesBrancheMax(highest_child));
    }
}
*/

void submit_vote(Protected *p)  {
    FILE *ostream = fopen("Pending_votes.txt","a"); //cree le fichier s'il n'existe pas
    if (!ostream)   {
        fprintf(stderr,"Erreur: submit_vote, output stream NULL\n");
        return;
    }
    char *vote = protected_to_str(p);
    fprintf(ostream,"%s\n",vote);
    free(vote);
    fclose(ostream);
}

void create_block(CellTree **tree, Key *author, int d)   {  //On a modifie la signature pour pouvoir acceder a la tete de l'arbre
    //Creation d'un bloc valide a partir de Pending_votes.txt
    CellProtected *votes = read_protected("Pending_votes.txt"); //ce qu'on met dans le bloc
    CellTree *leaf = last_node(*tree);
    unsigned char previous_hash[2*SHA256_DIGEST_LENGTH+1];
    int i;
    //On obtient le previous_hash
    if (leaf == NULL)   {   //Genesis Block
        for (i=0; i<(2*SHA256_DIGEST_LENGTH+1); i++)    {
            previous_hash[i] = '0';  
        }
        previous_hash[i] = '\0';
    } else {
        for (i=0; i<(2*SHA256_DIGEST_LENGTH+1); i++)    {
            previous_hash[i] = leaf->block->hash[i];  
        }
        previous_hash[i] = '\0';
    }

    Block *b = creerBlock(author,votes,(unsigned char *)"",previous_hash,0); // ne pas desallouer le bloc !
    compute_proof_of_work(b,d);
    fprintf(stderr,"create_block, verify_block %d\n",verify_block(b,d));
    CellTree *new = create_node(b);
    //On gere le Genesis Block de la chaine
    if (leaf == NULL)   {
        *tree = new;
    } else {    
        add_child(leaf,new);    //on sait que l'arbre est non vide
    }

    assert(remove("Pending_votes.txt") == 0);
    write_block("Pending_block.txt", b);
    //on conserve le block dans l'arbre
}

void add_block(int d, char *name)   {
    Block *b = lireBlock("Pending_block.txt");
    int verified = verify_block(b,d);
    fprintf(stderr,"\nadd_block : verified = %d (doit == 1)\n",verified);
    if (verified)   {
        char path[256] = "\0";
        strcat(path,"./Blockchain/");
        strcat(path,name);
        write_block(path, b);
    }
    assert(remove("Pending_block.txt") == 0);
    free(b->hash);
    free(b->previous_hash);
    delete_list_protected_total(b->votes);
    free(b);
}

CellTree *read_tree()   {
    DIR *rep = opendir("./Blockchain/");
    if (rep == NULL)    {
        fprintf(stderr, "Erreur : read_tree, ouverture du repertoire\n");
        return NULL;
    }
    //on compte d'abord le nombre de fichiers
    int nbFichiers = 0;
    struct dirent *dir;
    while ((dir = readdir(rep)))    {
        if (strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0)   {
            nbFichiers++;
        }
    }



    fprintf(stderr,"\nread_tree : nbFichiers dans Blockchain = %d\n",nbFichiers);



    //creation du tableau
    CellTree *tab[nbFichiers];
    for (int i=0; i<nbFichiers; i++)    {
        tab[i] = NULL;
    }
    //creation d'un noeud par fichier
    Block *b = NULL;
    char path[256];
    int i=0;
    while ((dir = readdir(rep)))    {
        if (strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0)   {
            path[0] = '\0';
            strcat(path,"./Blockchain/");
            strcat(path,dir->d_name);
            b = lireBlock(dir->d_name);
            tab[i] = create_node(b);
            i++;
        }
    }
    closedir(rep);

    //on ajoute a chaque noeud ses fils
    int pere,fils;
    for (pere=0; pere<nbFichiers; pere++)   {
        for (fils=0; fils<nbFichiers; fils++)   {
            if (strcmp((char *)tab[pere]->block->hash,(char *)tab[fils]->block->previous_hash) == 0)    {
                add_child(tab[pere],tab[fils]);
            }
        }
    }

    //on cherche la racine de l'arbre
    CellTree *racine = NULL;
    int nbRacines=0;    //verification de l'unicite de la racine
    for (i=0; i<nbFichiers; i++)    {
        if (tab[i]->father == NULL) {
            racine = tab[i];
            racine++;
        }
    }

    if (nbRacines == 1) {
        return racine;
    }
    else {
        fprintf(stderr,"Erreur : read_tree, racine non unique ou non existante\n");
        for (i=0; i<nbFichiers; i++)    {
            if (tab[i] == NULL) {
                fprintf(stderr,"tab[%d] NULL\n",i);
            } else {
                delete_node(tab[i]);
            }
        }
        return NULL;
    }
}

Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)  {
    //verification de sizeC >= len(candidates) && sizeV >= len(voters)
    assert(   (sizeC >= listKeyLength(candidates))   &&   (sizeV >= listKeyLength(voters))   );

    //extraction de la liste des declarations de vote valides
    CellProtected * votes = votesBrancheMax(tree);
    thwarted(&votes);

    //Calcul du gagnant
    Key *gagnant = compute_winner(votes, candidates, voters, sizeC, sizeV);
    
    //on libere les cellules mais pas les protected
    CellProtected *tmp;
    while (votes)   {
        tmp = votes;
        votes = votes->next;
        free(tmp);
    }
    return gagnant;
}







