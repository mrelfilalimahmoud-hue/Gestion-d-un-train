#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train_simple.h"


///Initialisation du train
Train *InitialiserTrain(void)
{
    Train *T = (Train*)malloc(sizeof(Train));
    T->tete=NULL;
    return T;
}
///création dynamique du train
Wagon* creerWagon(int id, const char* type, int capacite, const char* destination)
{
    Wagon *nouveau = (Wagon*)malloc(sizeof(Wagon));
    if (nouveau == NULL) return NULL;
    nouveau->id = id;
    nouveau->capacite = capacite;

    strncpy(nouveau->type, type, sizeof(nouveau->type) - 1);
    nouveau->type[sizeof(nouveau->type) - 1] = '\0'; // Garantie la fin du chaîne

    strncpy(nouveau->destination, destination, sizeof(nouveau->destination) - 1);
    nouveau->destination[sizeof(nouveau->destination) - 1] = '\0';

    nouveau->suivant = NULL;

    return nouveau;
}
///Ajout au debut
void ajouterDebut(Train *t, Wagon *nouveauWagon)
{
    if (t == NULL) {
        fprintf(stderr, "Erreur : Le Train est invalide.\n");
        return;
    }
    if (nouveauWagon == NULL) {
        fprintf(stderr, "Erreur : Le wagon a ajouter est invalide.\n");
        return;
    }

    nouveauWagon->suivant = t->tete;
    t->tete = nouveauWagon;

    printf("Succes : Wagon ID %d ajoute au debut du train.\n", nouveauWagon->id);
}

///Ajout à la fin
void ajouterFin(Train *t, Wagon *nouveauWagon)
{
    if (t == NULL || nouveauWagon == NULL) {
        fprintf(stderr, "Erreur : Le Train ou le Wagon est invalide.\n");
        return;
    }

    nouveauWagon->suivant = NULL;

    //Cas1 :Le train est completement vide
    if (t->tete == NULL) {
        t->tete = nouveauWagon;
        printf("Succes : Wagon ID %d ajoute (premier wagon du train).\n", nouveauWagon->id);
        return;
    }

    // Cas2 : Le train contient deja des wagons
    // Il faut parcourir la liste depuis la tete jusqu'au dernier wagon
    Wagon *actuel = t->tete;

    while (actuel->suivant != NULL) {
        actuel = actuel->suivant;
    }

    actuel->suivant = nouveauWagon;

    printf("Succes : Wagon ID %d ajoute a la fin du train.\n", nouveauWagon->id);
}

///Inserer un Wagon
void insererApres(Train *t, int idRecherche, Wagon *nouveauWagon) {
    if (t == NULL || nouveauWagon == NULL) {
        fprintf(stderr, "Erreur : Train ou wagon invalide.\n");
        return;
    }

    //Etape 1 : Recherche du wagon avec l'ID demande
    Wagon *actuel = t->tete;
    while (actuel != NULL && actuel->id != idRecherche) {
        actuel = actuel->suivant;
    }

    // Etape 2 : Verification si l'ID a ete trouve
    if (actuel == NULL) {
        fprintf(stderr, "Erreur : Le wagon avec l'ID %d est introuvable. Insertion annulee.\n", idRecherche);
        free(nouveauWagon);
        return;
    }

    //Etape 3 : L'insertion
    nouveauWagon->suivant = actuel->suivant;
    actuel->suivant = nouveauWagon;

    printf("Succes : Wagon ID %d insere apres le wagon ID %d.\n", nouveauWagon->id, idRecherche);
}

///Supprimer 1er Wagon
void supprimerWagon(Train *t, int idRecherche) {
    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }


    if (t->tete == NULL) {
        fprintf(stderr, "Erreur : Le train est vide. Suppression impossible.\n");
        return;
    }

    Wagon *actuel = t->tete;
    Wagon *precedent = NULL;

    if (actuel != NULL && actuel->id == idRecherche) {
        t->tete = actuel->suivant;
        free(actuel);

        printf("Succes : Wagon ID %d (en tete) supprime du train.\n", idRecherche);
        return;
    }


    while (actuel != NULL && actuel->id != idRecherche) {
        precedent = actuel;       // Le precedent prend la place de l'actuel
        actuel = actuel->suivant; // L'actuel avance d'un pas
    }


    if (actuel == NULL) {
        fprintf(stderr, "Erreur : Le wagon avec l'ID %d est introuvable.\n", idRecherche);
        return;
    }


    precedent->suivant = actuel->suivant;

    free(actuel);

    printf("Succes : Wagon ID %d supprime du train.\n", idRecherche);
}

///Affichage train
void afficherTrain(Train *t) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }


    if (t->tete == NULL) {
        printf("\n--- Le train est actuellement vide ---\n\n");
        return;
    }


    printf("\n========== COMPOSITION DU TRAIN ==========\n");

    Wagon *actuel = t->tete;
    int position = 1; // Pour afficher l'ordre des wagons (1er, 2eme, etc.)


    while (actuel != NULL) {
        printf("[Position %02d] -> ID: %d | Type: %-15s | Capacite: %3d | Destination: %s\n",
               position,
               actuel->id,
               actuel->type,
               actuel->capacite,
               actuel->destination);

        actuel = actuel->suivant;
        position++;
    }

    printf("==========================================\n\n");
}

///Recherche d'un Wagon
void rechercherWagon(Train *t, int idRecherche) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }


    if (t->tete == NULL) {
        fprintf(stderr, "Erreur : Le train est vide. Recherche impossible.\n");
        return;
    }


    Wagon *actuel = t->tete;
    int position = 1;

    while (actuel != NULL) {
        // Si on trouve l'ID, on affiche et on quitte la fonction directement
        if (actuel->id == idRecherche) {
            printf("\n--- Wagon Trouve (Position %d) ---\n", position);
            printf("ID          : %d\n", actuel->id);
            printf("Type        : %s\n", actuel->type);
            printf("Capacite    : %d places/tonnes\n", actuel->capacite);
            printf("Destination : %s\n", actuel->destination);
            printf("----------------------------------\n\n");
            return;
        }
        actuel = actuel->suivant;
        position++;
    }
    fprintf(stderr, "Erreur : Le wagon avec l'ID %d est introuvable dans ce train.\n", idRecherche);
}

///Compter le nbr total de Wagon
int compterWagons(Train *t) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return 0;
    }

    int cmpt = 0;
    Wagon *actuel = t->tete;


    while (actuel != NULL) {
        cmpt++;
        actuel = actuel->suivant;
    }

    printf("\n Le train contient un total de %d wagon(s).\n", cmpt);

    return cmpt;
}

///Calcul de capacite de Train
int calculerCapacite(Train *t) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return 0;
    }


    if (t->tete == NULL) {
        printf("\n Le train est vide. Capacite totale = 0.\n");
        return 0;
    }

    int cT = 0;
    Wagon *actuel = t->tete;


    while (actuel != NULL) {
        cT += actuel->capacite;
        actuel = actuel->suivant;
    }


    printf("\nLa capacite totale du train est de %d places/tonnes.\n", cT);

    return cT;
}
///Liberation de memoire
void libererTrain(Train *t) {

    if (t == NULL) {
        return;
    }

    Wagon *actuel = t->tete;
    Wagon *wagonASupprimer;


    while (actuel != NULL) {
        wagonASupprimer = actuel;
        actuel = actuel->suivant;

        free(wagonASupprimer); // Liberation du wagon
    }

    //Liberer la structure Train elle-meme
    free(t);

    printf("Succes : Toute la memoire du train a ete liberee avec succes.\n");
}


