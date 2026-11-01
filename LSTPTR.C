#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSTPTR.h"
#include "ELTPRIM.h"
#include "ELTUSER.h"


adjList creerListe(void)
{
    adjList l=(adjList)malloc(sizeof(laStruct));
    if (!l)
        printf("Probleme d'allocation de memoire.\n");
    l->lg=0;
    l->head=NULL;
    return l;
}

//********************************************//

void elementAffecter(ELEMENT* e1, ELEMENT e2)
{
    *e1=e2;
}

void elementDetruire(ELEMENT e)
{
    free(e->nom);
    free(e);
}
//********************************************//

Node creerNoeud(ELEMENT e, int weight)
{
    Node n=(Node)malloc(sizeof(structNode));
    if(!n)
        printf("Plus d'espace.\n");
    elementAffecter(&n->user, e);
    n->next=NULL;
    n->weight=weight;
    return n;
}

int inserer(adjList l, ELEMENT user, int weight)
{
    int success=1;
    l->lg++;
    Node n, p;
    n=creerNoeud(user, weight);
    p=l->head;
    while(p!=NULL){
        for(int i=0; i<l->lg; i++){
            p=p->next;
        }
    }
    p=n;
    n->next=NULL;
    l->lg++;
    return success;
}

void detruireNoeud(Node n)
{
    elementDetruire(n->user);
    free(n);
}
