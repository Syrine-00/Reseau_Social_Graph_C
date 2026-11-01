#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "LSTPTR.h"


//************************************************************************************//
adjList creerListe(void)
{
    adjList l=(adjList)malloc(sizeof(laStruct));
    if (!l)
        printf("Probleme d'allocation de memoire.\n");
    l->lg=0;
    l->head=NULL;
    return l;
}

//************************************************************************************//

Node creerNoeud(ELEMENT e, int weight)
{
    Node n=(Node)malloc(sizeof(structNode));
    if(!n)
        printf("Plus d'espace.\n");
    n->user=e;
    n->next=NULL;
    n->weight=weight;
    return n;
}

void detruireNoeud(Node n)
{
    elementDetruire(n->user);
    free(n);
}

//************************************************************************************//

graphePondere creerGraphe(int V)
{
    graphePondere g=malloc(sizeof(graphePondere));
    if(!g)
        printf("Probleme d'allocation de memoire.\n");
    g->V=V;

    g->utilisateurs=(ELEMENT*)malloc(V * sizeof(ELEMENT));
    if(!g->utilisateurs)
        printf("Probleme d'allocation de memoire.\n");

    for (int i=0; i<V; i++) {
        g->utilisateurs[i]=NULL;
    }

    g->adjList=(Node*)malloc(V * sizeof(Node));
    if(!g->adjList)
        printf("Probleme d'allocation de memoire.\n");

   for (int i=0; i<V; i++){
        g->adjList[i]=NULL;
    }
    return g;
}

//************************************************************************************//

int grapheVide(graphePondere g)
{
    int vide=0;
    if(g==NULL){
        printf("Graphe vide.\n");
        vide=1;
    }
    return vide;
}

//************************************************************************************//

int ajouterUtilisateur_dansGraphe(graphePondere g, ELEMENT user) {
    if (!g || !user) {
        printf("Erreur : graphe ou utilisateur inexistant\n");
        return 0;
    }

    int existe=0;
    for(int i=0; i<g->V; i++){
        if(g->utilisateurs[i]!=NULL && g->utilisateurs[i]->id==user->id){
            printf("Utilisateur avec l'ID %d existe deja!!\n", user->id);
            existe=1;
            break;
        }
    }
    if(existe)
        return;

    for (int i=0; i<g->V; i++){
        if (g->utilisateurs[i]==NULL) {
            g->utilisateurs[i]=user;
            printf("Utilisateur ajoute avec succes!\n");
            return 1;
        }
    }

    printf("Erreur : Pas de place pour ajouter un utilisateur.\n");
    return 0;
}

void ajouterUtilisateur(graphePondere g)
{
    ELEMENT user=elementLire();
    ajouterUtilisateur_dansGraphe(g, user);
}

//************************************************************************************//

void detruireGraphe(graphePondere g)
{
    if(grapheVide(g)){
        printf("Rien a detruire, le graphe n'existe pas.\n");
        return;
    }

    //liberation des sommets
    for (int i=0; i<g->V; i++) {
        if (g->utilisateurs[i]!=NULL) {
            supprimerUtilisateur(g, g->utilisateurs[i]->id);
        }
    }
    //liberation du tableau d'utilisateurs
    elementDetruire(g->utilisateurs);


    //liberation du graphe
    free(g);
}

//************************************************************************************//

int ajouterRelation(graphePondere g, int src, int dest, int poids)
{
    if (!g) {
        printf("Graphe inexistant.\n");
        return 0;
    }

    if (src>=g->V || dest>=g->V || src<0 || dest<0){
        printf("Indices invalides src=%d, dest=%d\n", src, dest);
        return 0;
    }

    int trouveSrc=0, trouveDest=0;
    for (int i=0; i<g->V; i++) {
        if (g->utilisateurs[i] && g->utilisateurs[i]->id==src){
            trouveSrc=1;
        }
        if (g->utilisateurs[i] && g->utilisateurs[i]->id==dest){
            trouveDest=1;
        }
    }

    if (!trouveSrc || !trouveDest) {
        printf("Erreur : Utilisateur source (%d) ou destination (%d) non trouvé.\n", src, dest);
        return 0;
    }

    if (!g->utilisateurs[src] || !g->utilisateurs[dest]) {
        printf("Erreur : utilisateur inexistant pour src=%d ou dest=%d\n", src, dest);
        return 0;
    }

    Node n1 = creerNoeud(g->utilisateurs[dest], poids);
    Node n2 = creerNoeud(g->utilisateurs[src], poids);
    if (!n1 || !n2) {
        printf("Erreur : echec de l'allocation memoire pour les noeuds\n");
        return 0;
    }


    n1->next = g->adjList[src];
    g->adjList[src] = n1;

    n2->next = g->adjList[dest];
    g->adjList[dest] = n2;


    return 1;
}

//************************************************************************************//

int supprimerRelation(graphePondere g, int src, int dest)
{
    if(!g){
        return 0;
    }

    if((src<0) || (src>(g->V)) || (dest<0) || (dest>(g->V))){
        printf("Source ou destination invalide.\n");
        return 0;}

    int id1=-1, id2=-1;
    for (int i=0; i<g->V; i++){
        if (g->utilisateurs[i] && g->utilisateurs[i]->id==src){
            id1=i;
        }
        if(g->utilisateurs[i] && g->utilisateurs[i]->id==dest){
            id2=i;
        }
    }
    if (id1==-1 || id2==-1){
        printf("Source ou destination introuvable.\n");
        return 0;
    }
    //supprimer dest de la liste d'adjacence de src
    Node p=g->adjList[src];
    Node q=NULL;

    while(p!=NULL){
        if(p->user->id==dest){
            if(q==NULL){ // premier element
                g->adjList[src]=p->next;
            } else{
                q->next=p->next;
            }
            free(p);
            break;
        }
        q=p;
        p=p->next;
    }

    //supprimer src de la liste d'adjacence de dest (graphe non oriente)
    p=g->adjList[dest];
    q=NULL;

    while(p!=NULL){
        if(p->user->id==src){
            if(q==NULL) {
                g->adjList[dest]=p->next;
            } else{
                q->next=p->next;
            }
            free(p);
            break;
        }
        q=p;
        p=p->next;
    }
    printf("Relation entre %d et %d supprimee avec succes!\n", src, dest);

    return 1;
    }

//************************************************************************************//
int supprimerUtilisateur(graphePondere g, int idUser)
{
    if (!g) return 0;

    int id=-1;
    for (int i=0; i<g->V; i++){
        if (g->utilisateurs[i] && g->utilisateurs[i]->id==idUser){
            id=i;
            break;
        }
    }
    if (id==-1){
        printf("Utilisateur introuvable.\n");
        return 0;
    }
    for (int i=0; i<g->V; i++){
        if (g->utilisateurs[i] && i!=id){
            supprimerRelation(g, idUser, g->utilisateurs[i]->id);
        }
    }

    Node courant=g->adjList[id];
    while (courant!=NULL) {
        Node suivant=courant->next;
        detruireNoeud(courant);
        courant=suivant;
    }
    g->adjList[id]=NULL;

    elementDetruire(g->utilisateurs[id]);
    g->utilisateurs[id]=NULL;

    printf("Utilisateur %d supprime avec succes.\n", idUser);
    return 1;
}


//************************************************************************************//

graphePondere chargerGraphe(const char* filename)
{
    FILE* file=fopen(filename, "r");
    if (!file) {
        printf("Impossible d'ouvrir le fichier %s.\n", filename);
        return NULL;
    }

    graphePondere g=creerGraphe(20);  //20 sommets max

    int src, dest, poids;
    char x[100];
    while (fgets(x, sizeof(x), file)){
        if (sscanf(x, " %d -- %d [label=%d];", &src, &dest, &poids)==3){
            ajouterRelation(g, src, dest, poids);
        }
    }
    fclose(file);
    return g;
}

//************************************************************************************//

void afficherGraphe(graphePondere g)
{
    if(grapheVide(g)){
        printf("Rien a afficher, le graphe n'existe pas.\n");
        return;
    }

    for(int i=0; i<g->V; i++){
        if(g->utilisateurs[i]){
            printf("%s(%d)", g->utilisateurs[i]->nom, g->utilisateurs[i]->id);
            Node temp=g->adjList[i];
            while(temp){
                if(temp->user->id>i){
                    printf("-------%d------ %s(%d)", temp->weight, temp->user->nom, temp->user->id);
                }
                temp=temp->next;
            }
        }
    }
}

//************************************************************************************//

void sauvegarderGraphe(graphePondere g, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file){
        printf("Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }
    fprintf(file, "graph G {\n");//graphviz format

    //parcourir chaque sommet du graphe
    for (int i=0; i<g->V; i++){
        Node temp=g->adjList[i];

        while (temp){
            int id1=g->utilisateurs[i]->id;
            int id2=temp->user->id;
            if (id1<id2) {  //eviter d'ecrire deux fois la meme arete (graphe non oriente)
                fprintf(file, "    %s -- %s [label=%d];\n", g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom, temp->weight);
            }
            temp=temp->next;
        }
    }
    fprintf(file, "}\n");  //ferme le fichier
    fclose(file);

    printf("Graphe enregistre dans %s\n", filename);
}

//************************************************************************************//

void chargerReseau(graphePondere g)
{
    if(!g){
        printf("Graphe vide.\n");
    }
    for(int i=0; i<g->V; i++){
        if(g->utilisateurs[i]!=NULL){
            printf("U %d %s %d\n", g->utilisateurs[i]->id, g->utilisateurs[i]->nom, g->utilisateurs[i]->age);
        }
    }

    //affichage des relations (eviter les doublons)
    int M[g->V][g->V]; //pour verifier les relations deja affichees
    memset(M, 0, sizeof(M));

    for(int i=0; i<g->V; i++){
        Node l=g->adjList[i];
        while (l){
            int src=i;

            int dest=l->user->id;
            int weight=l->weight;

            if(g->utilisateurs[src]!=NULL && g->utilisateurs[dest]!=NULL && !M[src][dest]){
                printf("R %d %d %d # %s %s\n",src, dest, weight, g->utilisateurs[src]->nom, g->utilisateurs[dest]->nom);
                M[src][dest]=1;
                M[dest][src]=1;
            }
            l=l->next;
        }
    }

}


//************************************************************************************//

void dfs(graphePondere g, int idUser, int* visite){
    Node temp=g->adjList[idUser];


    visite[idUser]=1;

    while(temp!=NULL){
        int idVoisin=temp->user->id;
        if(visite[idVoisin]==0){
            dfs(g, idVoisin, visite);
        }
        temp=temp->next;
    }

}

void DFS(graphePondere g, int idUser){
    if (!g || !g->utilisateurs[idUser]) {
        printf("Utilisateur invalide.\n");
        return;
    }
    int* visite=malloc(g->V * sizeof(int));
    for(int i=0; i<g->V; i++){
        visite[i]=0;
    }

    dfs(g, idUser, visite);
    printf("[%s", g->utilisateurs[idUser]->nom);
    for (int i=0; i<g->V; i++) {
            if (visite[i] && i != idUser) {
                printf(" %s", g->utilisateurs[i]->nom);
            }
        }
    printf("]\n");

    free(visite);
    return 0;
}



//************************************************************************************//

void bfs(graphePondere g, int idUser)
{
    if (!g || !g->utilisateurs[idUser]) {
        printf("Utilisateur invalide.\n");
        return;
    }

    int* visite=malloc(g->V * sizeof(int));
    int* niveau=malloc(g->V*sizeof(int));
    for (int i=0; i<g->V; i++) {
            visite[i]=0;
            niveau[i]=-1;
    }

    // file FIFO pour le parcours en largeur
    int* file=malloc(g->V * sizeof(int));
    int debut=0, fin = 0;

    // Initialisation
    file[fin++]=idUser;
    visite[idUser]=1;
    niveau[idUser]=0;

    // BFS
    while (debut<fin){
        int courant=file[debut++];
        Node temp=g->adjList[courant];

        while (temp){
            int idVoisin = temp->user->id;

            if (!visite[idVoisin]){
                visite[idVoisin]=1;
                niveau[idVoisin]=niveau[courant] + 1;
                file[fin++]=idVoisin;
            }
            temp=temp->next;
        }
    }

    // Affichage des niveaux
    for (int n=0; n<g->V; n++){
        int affichage=0;
        for (int i=0; i<g->V; i++){
            if (niveau[i]==n) {
                if (!affichage){
                    printf("Niveau %d: [ ", n);
                    affichage = 1;
                }
                printf("%s ", g->utilisateurs[i]->nom);
            }
        }
        if (affichage){
            printf("]\n");
        }
    }

    free(visite);
    free(niveau);
    free(file);
}

//************************************************************************************//

void dijkstra(graphePondere g, int src_id, int dest_id)
{
    int trouveSrc=0, trouveDest=0;


    int* dist=malloc(g->V * sizeof(int)); //dist min depuis src
    int* visiter=malloc(g->V * sizeof(int));
    int* prec=malloc(g->V * sizeof(int));
    int taille_prec=0;

    for (int i=0; i<g->V; i++){
        dist[i]=9999;
        visiter[i]=0;
        prec[i]=-1;
    }

    dist[src_id]=0;

    for(int i=0; i<g->V; i++){
        int min=9999;
        int u=-1;
        for(int j=0; j<g->V; j++){
            if(visiter[j]==0 && dist[j]<min){
                min=dist[j];
                u=j;
            }
        }
        if(u==-1) break;

        visiter[u]=1;

        Node voisin=g->adjList[u];
        while(voisin){
            int voisinId=voisin->user->id;
            int poids=voisin->weight;
            if(!visiter[voisinId] && dist[u]+poids<dist[voisinId]){
                dist[voisinId]=dist[u]+poids;
                prec[voisinId]=u;
                taille_prec++;
            }
            voisin=voisin->next;
        }
    }

    if(dist[dest_id]==9999){
        printf("Aucun chemin trouve entre %s et %s.\n", g->utilisateurs[src_id]->nom, g->utilisateurs[dest_id]->nom);
    }else{
        int chemin[100];
        int taille = 0;
        for (int v=dest_id; v!=-1; v=prec[v]){
            chemin[taille++]=v;
        }
        printf("Chemin :");
        for(int i=taille-1; i>=0; i--){
            if(g->utilisateurs[i]!=NULL) printf("%s ", g->utilisateurs[chemin[i]]->nom);
        }
        printf("\nPoids total: %d\n", dist[dest_id]);
    }
    free(dist);
    free(visiter);
    free(prec);

}

//************************************************************************************//

int* bfs_sansprint(graphePondere g, int idUser)
{
    if (!g || idUser<0 || idUser>=g->V || !g->utilisateurs[idUser]) {
        return;
    }

    int* visite=malloc(g->V * sizeof(int));
    int* niveau=malloc(g->V*sizeof(int));
    for (int i=0; i<g->V; i++) {
            visite[i]=0;
            niveau[i]=-1;
    }

    // file FIFO pour le parcours en largeur
    int* file=malloc(g->V * sizeof(int));
    int debut=0, fin = 0;

    // Initialisation
    file[fin++]=idUser;
    visite[idUser]=1;
    niveau[idUser]=0;

    // BFS
    while (debut<fin){
        int courant=file[debut++];
        Node temp=g->adjList[courant];

        while (temp){
            int idVoisin = temp->user->id;

            if (!visite[idVoisin]){
                visite[idVoisin]=1;
                niveau[idVoisin]=niveau[courant]+1;
                file[fin++]=idVoisin;
            }
            temp=temp->next;
        }
    }

    free(visite);
    free(file);

    return niveau;
}

//*********************************************************************************//


void trouver_communautes(graphePondere g){
    if(!g)
        return;

    int* visites=malloc(g->V * sizeof(int));
    for (int i=0; i<g->V; i++){
        visites[i]=0;}

    int c=1;
    for(int i=0; i<g->V; i++){
        if(visites[i]==0){
            int* niveau=bfs_sansprint(g, i);
            if(!niveau) continue;
            printf("Communaute %d: [", c++);
            for(int j=0; j<g->V; j++){
                if(niveau[j]!=-1 && visites[j]==0){
                    printf(" %s", g->utilisateurs[j]->nom);
                    visites[j]=1;
                }
            }
            free(niveau);
            printf(" ]\n");
        }
    }
    free(visites);
}

//************************************************************************************//
