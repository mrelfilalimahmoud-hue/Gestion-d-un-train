#ifndef TRAIN_SIMPLE_H
#define TRAIN_SIMPLE_H
///---------------------------PHASE 1---------------------------------

/// Structure d'un wagon (Phase 1 : liste simple)
typedef struct Wagon {
    int id;
    char type[30];
    int capacite;
    char destination[40];
    struct Wagon *suivant;
} Wagon;

/// Structure du train
typedef struct Train {
    Wagon *tete;
} Train;


Train *InitialiserTrain(void);
Wagon* creerWagon(int id, const char* type, int capacite, const char* destination);
void ajouterDebut(Train *t, Wagon *nouveauWagon) ;
void ajouterFin(Train *t, Wagon *nouveauWagon);
void insererApres(Train *t, int idRecherche, Wagon *nouveauWagon);
void supprimerWagon(Train *t, int idRecherche);
void afficherTrain(Train *t);
void rechercherWagon(Train *t, int idRecherche);
int compterWagons(Train *t);
int calculerCapacite(Train *t);
void libererTrain(Train *t);
///----------------------------------------------------------------



#endif // TRAIN_SIMPLE_H
