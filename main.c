#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "ELTUSER.h"
#include "graph.h"


void afficherMenu() {
    printf("\n");
    printf("\n================================ RESEAU SOCIAL--MENU PRINCIPAL ==========================\n");
    printf("\n");
    printf("                             1. [+ USER] Ajouter un utilisateur\n");
    printf("                             2. [- USER] Supprimer un utilisateur\n");
    printf("                             3. [+ REL] Ajouter une relation\n");
    printf("                             4. [- REL] Supprimer une relation\n");
    printf("                             5. [AFFICH] Afficher le reseau\n");
    printf("                             6. [SAUV] Sauvegarder le graphe\n");
    printf("                             7. [DFS] Trouver des amis accessibles directs ou indirectes\n");
    printf("                             8. [BFS] Trouver des amis à une distance\n");
    printf("                             9. [DIJK] Trouver le chemin le plus court (Dijkstra)\n");
    printf("                             10.[COMM] Trouver les communautes du reseau\n");
    printf("                             11.[AFFICH] Afficher le graphe\n");
    printf("                             12. QUITTER\n");
    printf("\n");
    printf("=======================================================================================\n");
    printf("\n");
    printf("Choix: ");
}

int main() {
    const char* filename = "graphe.dot";


    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "graph G {\n"); //debut du graphe
        fclose(file);
    }
    graphePondere g=creerGraphe(20);
    int choix;
    int id1, id2;

    ELEMENT user1 = elementCreer();
    user1->id = 0;  // Ajoute un ID valide
    strcpy(user1->nom, "Ahmed");
    user1->age=20;
    ajouterUtilisateur_dansGraphe(g, user1);

    ELEMENT user2 = elementCreer();
    user2->id = 1;
    strcpy(user2->nom, "Karim");
    user2->age=20;
    ajouterUtilisateur_dansGraphe(g, user2);

    ELEMENT user3 = elementCreer();
    user3->id = 2;
    strcpy(user3->nom, "Rania");
    user3->age=20;
    ajouterUtilisateur_dansGraphe(g, user3);

    ELEMENT user4 = elementCreer();
    user4->id = 3;
    strcpy(user4->nom, "Youssef");
    user4->age=20;
    ajouterUtilisateur_dansGraphe(g, user4);

    ELEMENT user5 = elementCreer();
    user5->id = 4;
    strcpy(user5->nom, "Samira");
    user5->age=20;
    ajouterUtilisateur_dansGraphe(g, user5);

    ajouterRelation(g, 0, 1, 5);
    ajouterRelation(g, 0, 2, 3);
    ajouterRelation(g, 1, 3, 2);
    ajouterRelation(g, 2, 3, 4);
    ajouterRelation(g, 3, 4, 1);

    for(int i=0; i<20; i++){
        printf("\n");
    }

    //ctrl de saisie pour les id
    int saisirEntier() {
        int valeur;
        while (scanf("%d", &valeur)!=1) {
            printf("Entree invalide. Veuillez entrer un nombre entier: ");
            while (getchar()!='\n');
        }
        return valeur;
    }



    do{
        afficherMenu();
        scanf("%d", &choix);
        getchar();

        switch(choix){
            case 1:
                ajouterUtilisateur(g);
                break;
            case 2:
                printf("Choisir l'un des utilisateurs a supprimer: \n");
                for(int i=0; i<g->V; i++){
                    if(g->utilisateurs[i]!=NULL){
                        printf("U %d %s\n", g->utilisateurs[i]->id, g->utilisateurs[i]->nom);
                    }
                }
                printf("Entrer ID utilisateur a supprimer: ");
                id1=saisirEntier();
                supprimerUtilisateur(g, id1);
                break;
            case 3:
                printf("Entrer ID source: ");
                id1=saisirEntier();
                printf("Entrer ID destination: ");
                id2=saisirEntier();
                printf("Entrer poids (force relation): ");
                int poids;
                poids=saisirEntier();
                ajouterRelation(g, id1, id2, poids);
                if(ajouterRelation(g, id1, id2, poids)==1) printf("Relation ajoutee avec succes!");
                break;
            case 4:
                printf("Entrer ID source: ");
                id1=saisirEntier();
                printf("Entrer ID destination: ");
                id2=saisirEntier();
                supprimerRelation(g, id1, id2);
                break;
            case 5:
                chargerReseau(g);
                break;
            case 6:
                sauvegarderGraphe(g, "graphe.dot");
                break;
            case 7:
                printf("Entrer ID utilisateur pour DFS: ");
                id1=saisirEntier();
                DFS(g, id1);
                break;
            case 8:
                printf("Entrer ID utilisateur pour BFS: ");
                id1=saisirEntier();
                bfs(g, id1);
                break;
            case 9:
                printf("Entrer ID source: ");
                id1=saisirEntier();
                printf("Entrer ID destination: ");
                id2=saisirEntier();
                dijkstra(g, id1, id2);
                break;
            case 10:
                trouver_communautes(g);
                break;
            case 11:
                afficherGraphe(g);
                break;
            case 12:
                printf("Fermeture du programme...\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    }while(choix!=12);

    detruireGraphe(g);
    return 0;
}



