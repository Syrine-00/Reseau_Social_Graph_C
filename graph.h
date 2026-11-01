#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "LSTPTR.h"

//definition d'un graphe
typedef struct
{
    int V;
    ELEMENT* utilisateurs;
    Node* adjList;
}*graphePondere;

typedef FILE *graphFile;



graphePondere creerGraphe(int V);
void detruireGraphe(graphePondere g);
int grapheVide(graphePondere g);
int ajouterUtilisateur_dansGraphe(graphePondere g, ELEMENT user);
int supprimerUtilisateur(graphePondere g, int idUser);
int ajouterRelation(graphePondere g, int src, int dest, int poids);
int supprimerRelation(graphePondere g, int src, int dest);
void afficherGraphe(graphePondere g);
graphePondere chargerGraphe(const char* graphFile);
void sauvegarderGraphe(graphePondere g, const char* filename);
void chargerReseau(graphePondere g);
void dfs(graphePondere g, int idUser, int* visite);
void DFS(graphePondere g, int idUser);
void bfs(graphePondere g, int idUser);
void dijkstra(graphePondere g, int src_id, int dest_id);
int* bfs_sansprint(graphePondere g, int idUser);
void trouver_communautes(graphePondere g);


void detruireNoeud(Node n);
Node creerNoeud(ELEMENT e, int weight);


#endif // GRAPH_H_INCLUDED
