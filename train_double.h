#ifndef TRAIN_DOUBLE_H
#define TRAIN_DOUBLE_H
///---------------------------PHASE 2---------------------------------

/// Structure d'un wagon (Phase 2 : liste double)
typedef struct WagonD {
    int id;
    char type[30];
    int capacite;
    char destination[40];
    struct WagonD *precedent;
    struct WagonD *suivant;
} WagonD;

/// Structure du train
typedef struct TrainD {
    WagonD *tete;
    WagonD *queue;
} TrainD;


TrainD* initialiserTrain_d(void);
WagonD* creerWagon_d(int id, const char* type, int capacite, const char* destination);
void ajouterDebut_d(TrainD *t, WagonD *nouveauWagon);
void ajouterFin_d(TrainD *t, WagonD *nouveauWagon);
void insererApres_d(TrainD *t, int idRecherche, WagonD *nouveauWagon);
void supprimerWagon_d(TrainD *t, int idRecherche);
void afficherTrain_d(TrainD *t);
void rechercherWagon_d(TrainD *t, int idRecherche);
int compterWagons_d(TrainD *t);
int calculerCapacite_d(TrainD *t);
void libererTrain_d(TrainD *t);
void parcourirAllerRetour_d(TrainD *t);
void insererAvant_d(TrainD *t, int idRecherche, WagonD *nouveauWagon);
void suppFinRap_d(TrainD *t);
void deplacerWagon_d(TrainD *t, int posSource, int posDest);
void afficherTrainInverse_d(TrainD *t);
#endif // TRAIN_DOUBLE_H
