#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ELTUSER.h"
#include "ELTPRIM.h"

ELEMENT elementCreer(void)
{
    ELEMENT e;
    e=(ELEMENT)malloc(sizeof(UtilisateurStruct));
    if (!e) {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }
    return e;
}

//implementation des primitives
ELEMENT elementLire()
{
    ELEMENT elt = elementCreer();
    printf("\nID: ");
    while (scanf("%d", &elt->id)!=1){
        printf("Entree invalide. Reessayez: ");
        while(getchar()!='\n');
    }
    while(getchar()!='\n');
    printf("Nom: ");
    fgets(elt->nom, sizeof(elt->nom), stdin);
    elt->nom[strcspn(elt->nom, "\n")]=0; //supprimer le \n à la fin

    printf("Age: ");
    while (scanf("%d", &elt->age)!=1) {
        printf(">> Entrée invalide. Reessayez: ");
        while(getchar()!='\n');
    }
    while(getchar()!='\n');

    printf("\n");
    return elt;
}


//************************************************************************************//
void elementAfficher(ELEMENT *elt)
{
    printf("\nID: %d", (*elt)->id);
    printf("\nNom: %s", (*elt)->nom);
    printf("\nAge: %d", (*elt)->age);
}
//************************************************************************************//
void elementAffecter(ELEMENT* e1, ELEMENT e2)
{
    *e1=e2;
}
//************************************************************************************//
void elementCopier(ELEMENT* e1, ELEMENT e2)
{
    (*e1)->id=e2->id;
    strcpy((*e1)->nom, e2->nom);
    (*e1)->age=e2->age;
}
//************************************************************************************//
void elementComparer(ELEMENT e1, ELEMENT e2)
{
    return ((e1->id)-(e2->id));
}

//************************************************************************************//
void elementDetruire(ELEMENT e)
{
    free(e);
}
