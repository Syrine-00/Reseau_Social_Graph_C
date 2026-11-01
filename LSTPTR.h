#ifndef LSTPTR_H
#define LSTPTR_H
#include "ELTUSER.h"

//definition d'un noeud (sommet)
typedef struct structNode
{
    ELEMENT user;
    int weight;
    struct structNode* next;
}structNode, *Node;


//definition d'une liste d'adjacence
typedef struct laStruct {
    Node head;
    int lg;
} laStruct;

typedef laStruct* adjList;

adjList creerListe(void);

Node creerNoeud(ELEMENT e, int weight);
void detruireNoeud(Node n);
int inserer(adjList l, ELEMENT user, int weight);

void elementDetruire(ELEMENT);



#endif
