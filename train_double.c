#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train_double.h"
///Initialisation
TrainD* initialiserTrain_d(void)
{
    TrainD *T = (TrainD*)malloc(sizeof(TrainD));

    if (T == NULL) {
        fprintf(stderr, "Erreur critique : Echec de l'allocation memoire pour le train.\n");
        return NULL;
    }

    T->tete = NULL;
    T->queue = NULL;

    return T;

}

///création dynamique du train
WagonD* creerWagon_d(int id, const char* type, int capacite, const char* destination)
{
    WagonD *nouveau = (WagonD*)malloc(sizeof(WagonD));

    if (nouveau == NULL) {
        fprintf(stderr, "Erreur critique : Echec d'allocation memoire pour le wagon %d.\n", id);
        return NULL;
    }

    nouveau->id = id;
    nouveau->capacite = capacite;

    strncpy(nouveau->type, type, sizeof(nouveau->type) - 1);
    nouveau->type[sizeof(nouveau->type) - 1] = '\0';

    strncpy(nouveau->destination, destination, sizeof(nouveau->destination) - 1);
    nouveau->destination[sizeof(nouveau->destination) - 1] = '\0';

    nouveau->suivant = NULL;
    nouveau->precedent = NULL;

    return nouveau;
}

///Ajout au debut
void ajouterDebut_d(TrainD *t, WagonD *nouveauWagon) {
     if (t == NULL || nouveauWagon == NULL) {
        fprintf(stderr, "Erreur : Train ou wagon invalide.\n");
        return;
    }
    nouveauWagon->suivant = t->tete;
    nouveauWagon->precedent = NULL;
    if (t->tete == NULL) {

        t->queue = nouveauWagon;
    }
     else {

        t->tete->precedent = nouveauWagon;
    }
    t->tete = nouveauWagon;
    printf("Succes : Wagon ID %d ajoute au debut du train.\n", nouveauWagon->id);
}

///Ajout à la fin
void ajouterFin_d(TrainD *t, WagonD *nouveauWagon) {
    if (t == NULL || nouveauWagon == NULL) {
        fprintf(stderr, "Erreur : Le train ou le wagon est invalide.\n");
        return;
    }
    nouveauWagon->suivant = NULL;
    nouveauWagon->precedent = t->queue;
    if (t->queue == NULL) {
        t->tete = nouveauWagon;
    } else {
        t->queue->suivant = nouveauWagon;
    }
    t->queue = nouveauWagon;
    printf("Succes : Wagon ID %d ajoute a la fin.\n", nouveauWagon->id);
}

///Inserer un Wagon
void insererApres_d(TrainD *t, int idRecherche, WagonD *nouveauWagon) {

    if (t == NULL || nouveauWagon == NULL) {
        fprintf(stderr, "Erreur : Train ou wagon invalide.\n");
        return;
    }
    WagonD *actuel = t->tete;
    while (actuel != NULL && actuel->id != idRecherche) {
        actuel = actuel->suivant;
    }
    if (actuel == NULL) {
        fprintf(stderr, "Erreur : Le wagon avec l'ID %d est introuvable.\n", idRecherche);
        free(nouveauWagon);
        return;
    }
    nouveauWagon->suivant = actuel->suivant;
    nouveauWagon->precedent = actuel;
    if (actuel->suivant != NULL) {
        actuel->suivant->precedent = nouveauWagon;
    } else {

        t->queue = nouveauWagon;
    }
    actuel->suivant = nouveauWagon;
    printf("Succes : Wagon ID %d insere apres le wagon ID %d.\n", nouveauWagon->id, idRecherche);
}

///Supprimer 1er Wagon

void supprimerWagon_d(TrainD *t, int idRecherche) {
    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }

    if (t->tete == NULL) {
        fprintf(stderr, "Erreur : Le train est vide. Suppression impossible.\n");
        return;
    }

    WagonD *actuel = t->tete;
    while (actuel != NULL && actuel->id != idRecherche) {
        actuel = actuel->suivant;
    }
    if (actuel == NULL) {
        fprintf(stderr, "Erreur : Le wagon avec l'ID %d est introuvable.\n", idRecherche);
        return;
    }
    if (actuel == t->tete && actuel == t->queue) {
        // CAS 1 : C'est le SEUL wagon du train
        t->tete = NULL;
        t->queue = NULL;
    }
    else if (actuel == t->tete) {
        // CAS 2 : C'est le PREMIER wagon (mais il y en a d'autres apres)
        t->tete = actuel->suivant;
        t->tete->precedent = NULL;
    }
    else if (actuel == t->queue) {
        // CAS 3 : C'est le DERNIER wagon (mais il y en a d'autres avant)
        t->queue = actuel->precedent;
        t->queue->suivant = NULL;
    }
    else {
        // CAS 4 : C'est un wagon au MILIEU du train

        actuel->precedent->suivant = actuel->suivant;
        actuel->suivant->precedent = actuel->precedent;
    }
    free(actuel);
    printf("Succes : Wagon ID %d supprime du train (Phase 2).\n", idRecherche);
}

///Affichage train
void afficherTrain_d(TrainD *t) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le train est invalide.\n");
        return;
    }
    if (t->tete == NULL) {
        printf("\n--- Le train est actuellement vide ---\n\n");
        return;
    }
    printf("\n========== COMPOSITION DU TRAIN (PHASE 2) ==========\n");
    WagonD *actuel = t->tete;
    int position = 1;

    while (actuel != NULL) {
        printf("[Position %02d] -> ID: %d | Type: %-15s | Capacite: %3d | Dest: %s\n",
               position,
               actuel->id,
               actuel->type,
               actuel->capacite,
               actuel->destination);

        actuel = actuel->suivant;
        position++;
    }
    printf("====================================================\n\n");
}

///Rechercher Wagon
void rechercherWagon_d(TrainD *t, int idRecherche) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }
    if (t->tete == NULL) {
        fprintf(stderr, "Erreur : Le train est vide. Recherche impossible.\n");
        return;
    }
    WagonD *actuel = t->tete;
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
int compterWagons_d(TrainD *t) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return 0;
    }

    int cmpt = 0;
    WagonD *actuel = t->tete;


    while (actuel != NULL) {
        cmpt++;
        actuel = actuel->suivant;
    }

    printf("\n Le train contient un total de %d wagon(s).\n", cmpt);

    return cmpt;
}

///Calcul de capacite de Train
int calculerCapacite_d(TrainD *t) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return 0;
    }


    if (t->tete == NULL) {
        printf("\n Le train est vide. Capacite totale = 0.\n");
        return 0;
    }

    int cT = 0;
    WagonD *actuel = t->tete;


    while (actuel != NULL) {
        cT += actuel->capacite;
        actuel = actuel->suivant;
    }


    printf("\nLa capacite totale du train est de %d places/tonnes.\n", cT);

    return cT;
}
///Liberation de memoire
void libererTrain_d(TrainD *t) {

    if (t == NULL) {
        return;
    }

    WagonD *actuel = t->tete;
    WagonD *wagonASupprimer;


    while (actuel != NULL) {
        wagonASupprimer = actuel;
        actuel = actuel->suivant;

        free(wagonASupprimer); // Liberation du wagon
    }

    //Liberer la structure Train elle-meme
    free(t);

    printf("Succes : Toute la memoire du train a ete liberee avec succes.\n");
}

///Parcourir d->g et g->d
void parcourirAllerRetour_d(TrainD *t) {
    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }

    if (t->tete == NULL) {
        printf("\n Le train est vide.\n");
        return;
    }
    WagonD *actuel;
    printf("\n========== PARCOURS ALLER-RETOUR ==========\n");

    // 1. Parcours de gauche a droite (Aller)
    printf("[TETE] ");
    actuel = t->tete;
    while (actuel != NULL) {
        printf("-> [ID:%d] ", actuel->id);
        actuel = actuel->suivant;
    }
    printf("-> [QUEUE]\n");
    // 2. Parcours de droite a gauche (Retour)
    printf("[QUEUE] ");
    actuel = t->queue;
    while (actuel != NULL) {
        printf("-> [ID:%d] ", actuel->id);
        actuel = actuel->precedent;
    }
    printf("-> [TETE]\n");
}

///Insertion avant
void insererAvant_d(TrainD *t, int idRecherche, WagonD *nouveauWagon) {
    if (t == NULL || nouveauWagon == NULL) {
        fprintf(stderr, "Erreur : Train ou wagon invalide.\n");
        return;
    }
    if (t->tete == NULL) {
        fprintf(stderr, "Erreur : Le train est vide. Insertion impossible.\n");
        free(nouveauWagon); /* GESTION MEMOIRE : Eviter la fuite */
        return;
    }
    WagonD *actuel = t->tete;
    while (actuel != NULL && actuel->id != idRecherche) {
        actuel = actuel->suivant;
    }
    if (actuel == NULL) {
        fprintf(stderr, "Erreur : Le wagon avec l'ID %d est introuvable.\n", idRecherche);
        free(nouveauWagon);
        return;
    }
    nouveauWagon->suivant = actuel;
    nouveauWagon->precedent = actuel->precedent;
    if (actuel == t->tete) {
        // Cas particulier : 'actuel' est la tete du train !

        t->tete = nouveauWagon;
    } else {
        // Cas general : 'actuel' a un wagon avant lui

        actuel->precedent->suivant = nouveauWagon;
    }
    actuel->precedent = nouveauWagon;
    printf("Succes : Wagon ID %d insere avant le wagon ID %d.\n", nouveauWagon->id, idRecherche);
}

///Suppression dernier
void suppFinRap_d(TrainD *t) {

    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }
    if (t->queue == NULL) {
        fprintf(stderr, "Erreur : Le train est vide. Suppression impossible.\n");
        return;
    }
    WagonD *wagonASupprimer = t->queue;
    int idSupprime = wagonASupprimer->id;
    if (t->tete == t->queue) {
        t->tete = NULL;
        t->queue = NULL;
    } else {
        t->queue = wagonASupprimer->precedent;
        t->queue->suivant = NULL;
    }
    free(wagonASupprimer);
    printf("Succes : Le dernier wagon (ID %d) a ete supprime.\n", idSupprime);
}

///Deplacer wagon
void deplacerWagon_d(TrainD *t, int posSource, int posDest) {
    if (t == NULL || t->tete == NULL || posSource == posDest) return;

    // 1. Trouver le wagon source (cible)
    WagonD *cible = t->tete;
    int pos = 1;
    while (cible != NULL && pos < posSource) {
        cible = cible->suivant; pos++;
    }
    if (cible == NULL) return; // Position invalide

    // 2. EXTRACTION DE LA CIBLE
    if (cible->precedent != NULL)
        cible->precedent->suivant = cible->suivant;
    else
        t->tete = cible->suivant;

    if (cible->suivant != NULL)
        cible->suivant->precedent = cible->precedent;
    else
        t->queue = cible->precedent;

    cible->suivant = NULL;
    cible->precedent = NULL;

    // 3. Trouver la nouvelle position
    WagonD *nvPos = t->tete;
    pos = 1;
    while (nvPos != NULL && pos < posDest) {
        nvPos = nvPos->suivant; pos++;
    }

    // 4. REINSERTION
    if (nvPos == NULL) {
        // Insertion a la fin
        t->queue->suivant = cible;
        cible->precedent = t->queue;
        t->queue = cible;
    } else {
        // Insertion avant nvPos
        cible->suivant = nvPos;
        cible->precedent = nvPos->precedent;

        if (nvPos->precedent != NULL)
            nvPos->precedent->suivant = cible;
        else
            t->tete = cible;

        nvPos->precedent = cible;
    }
    printf("Wagon deplace avec succes.\n");
}

///Affichage Inverse
void afficherTrainInverse_d(TrainD *t) {
    if (t == NULL) {
        fprintf(stderr, "Erreur : Le pointeur du train est invalide.\n");
        return;
    }
    if (t->queue == NULL) {
        printf("\n--- Le train est actuellement vide ---\n\n");
        return;
    }
    printf("\n========== COMPOSITION INVERSE ==========\n");
    WagonD *actuel = t->queue;
    int position = compterWagons_d(t);
    while (actuel != NULL) {
        printf("[Position %02d] -> ID: %d | Type: %-15s | Capacite: %3d | Dest: %s\n",
               position,
               actuel->id,
               actuel->type,
               actuel->capacite,
               actuel->destination);

        actuel = actuel->precedent; /* On recule */
        position--; /* La position descend (ex: 4, 3, 2, 1) */
    }
}

