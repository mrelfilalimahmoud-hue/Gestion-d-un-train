#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train_simple.h"
#include "train_double.h"

int main()
{
    printf("Hello world!\n");
    /*Train *monTrain = InitialiserTrain();

    int choix;
    int id, capacite, idRecherche;
    char type[30], destination[40];
    Wagon *nouveauWagon;


    do {
        // Affichage du menu
        printf("\n========== GESTION D'UN TRAIN ==========\n");
        printf("1. Ajouter un wagon au debut\n");
        printf("2. Ajouter un wagon a la fin\n");
        printf("3. Inserer un wagon apres un id\n");
        printf("4. Supprimer un wagon\n");
        printf("5. Rechercher un wagon\n");
        printf("6. Afficher le train\n");
        printf("7. Nombre total de wagons\n");
        printf("8. Capacite totale\n");
        printf("9. Quitter\n");
        printf("========================================\n");
        printf("Votre choix : ");


        if (scanf("%d", &choix) != 1) {

            printf("Erreur de saisie. Veuillez entrer un nombre.\n");
            while(getchar() != '\n'); //Nettoyage du buffer
            continue;
        }


        switch (choix) {
            case 1:
            case 2:
                // On regroupe la saisie pour les cas 1 et 2 car c'est la meme
                printf("\n--- Saisie des donnees du wagon ---\n");
                printf("ID : "); scanf("%d", &id);


                printf("Type (ex: Voyageurs, Marchandises) : ");
                scanf(" %29[^\n]", type);

                printf("Capacite : "); scanf("%d", &capacite);

                printf("Destination : ");
                scanf(" %39[^\n]", destination);


                nouveauWagon = creerWagon(id, type, capacite, destination);

                if (choix == 1) ajouterDebut(monTrain, nouveauWagon);
                else ajouterFin(monTrain, nouveauWagon);
                break;

            case 3:
                printf("\nID du wagon existant (apres lequel inserer) : ");
                scanf("%d", &idRecherche);

                printf("\n--- Saisie des donnees du NOUVEAU wagon ---\n");
                printf("Nouvel ID : "); scanf("%d", &id);
                printf("Type : "); scanf(" %29[^\n]", type);
                printf("Capacite : "); scanf("%d", &capacite);
                printf("Destination : "); scanf(" %39[^\n]", destination);

                nouveauWagon = creerWagon(id, type, capacite, destination);
                insererApres(monTrain, idRecherche, nouveauWagon);
                break;

            case 4:
                printf("\nID du wagon a supprimer : ");
                scanf("%d", &idRecherche);
                supprimerWagon(monTrain, idRecherche);
                break;

            case 5:
                printf("\nID du wagon a rechercher : ");
                scanf("%d", &idRecherche);
                rechercherWagon(monTrain, idRecherche);
                break;

            case 6:
                afficherTrain(monTrain);
                break;

            case 7:
                compterWagons(monTrain);
                break;

            case 8:
                calculerCapacite(monTrain);
                break;

            case 9:
                printf("\nFermeture de l'application...\n");
                libererTrain(monTrain);
                break;

            default:
                printf("\nErreur : Choix invalide. Veuillez choisir entre 1 et 9.\n");
                break;
        }

    } while (choix != 9);*/

    ///-------------------------------------Phase 2---------------------------------




    TrainD *monTrain = initialiserTrain_d();
    int choix;

    // Variables pour la saisie
    int id, capacite, idRecherche, posSrc, posDest;
    char type[30], destination[40];
    WagonD *nouveauWagon = NULL;

    while (1) {
        printf("\n========== GESTION D'UN TRAIN (PHASE 2) ==========\n");
        printf("1. Ajouter un wagon au debut\n");
        printf("2. Ajouter un wagon a la fin\n");
        printf("3. Inserer un wagon apres un id\n");
        printf("4. Inserer un wagon avant un id\n");
        printf("5. Supprimer un wagon (par ID)\n");
        printf("6. Supprimer rapidement le dernier wagon\n");
        printf("7. Deplacer un wagon d'une position a une autre\n");
        printf("8. Rechercher un wagon\n");
        printf("9. Afficher le train (Gauche a Droite)\n");
        printf("10. Afficher le train inverse (Droite a Gauche)\n");
        printf("11. Parcourir de gauche a droite puis droite a gauche\n");
        printf("12. Nombre total de wagons\n");
        printf("13. Capacite totale du train\n");
        printf("14. Vider le train (Liberer la memoire)\n");
        printf("15. Quitter\n");
        printf("==================================================\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            while(getchar() != '\n'); // Vider le buffer si erreur de saisie
            continue;
        }

        switch (choix) {
            case 1:
            case 2:
            case 3:
            case 4:
                // Saisie commune pour la creation d'un wagon
                printf("\n--- Saisie des donnees du wagon ---\n");
                printf("ID : "); scanf("%d", &id);
                printf("Type (ex: Voyageurs, Marchandises) : "); scanf("%29s", type);
                printf("Capacite : "); scanf("%d", &capacite);
                printf("Destination : "); scanf("%39s", destination);
                nouveauWagon = creerWagon_d(id, type, capacite, destination);

                if (choix == 1) {
                    ajouterDebut_d(monTrain, nouveauWagon);
                } else if (choix == 2) {
                    ajouterFin_d(monTrain, nouveauWagon);
                } else if (choix == 3) {
                    printf("Apres quel ID voulez-vous inserer ? : ");
                    scanf("%d", &idRecherche);
                    insererApres_d(monTrain, idRecherche, nouveauWagon);
                } else if (choix == 4) {
                    printf("Avant quel ID voulez-vous inserer ? : ");
                    scanf("%d", &idRecherche);
                    insererAvant_d(monTrain, idRecherche, nouveauWagon);
                }
                break;

            case 5:
                printf("\nID du wagon a supprimer : ");
                scanf("%d", &idRecherche);
                supprimerWagon_d(monTrain, idRecherche);
                break;

            case 6:
                suppFinRap_d(monTrain);
                break;

            case 7:
                printf("\nPosition source du wagon : ");
                scanf("%d", &posSrc);
                printf("Position de destination : ");
                scanf("%d", &posDest);
                deplacerWagon_d(monTrain, posSrc, posDest);
                break;

            case 8:
                printf("\nID du wagon a rechercher : ");
                scanf("%d", &idRecherche);
                rechercherWagon_d(monTrain, idRecherche);
                break;

            case 9:
                afficherTrain_d(monTrain);
                break;

            case 10:
                afficherTrainInverse_d(monTrain);
                break;

            case 11:
                parcourirAllerRetour_d(monTrain);
                break;

            case 12:
                // La fonction retourne un int, on peut l'afficher ici si elle ne le fait pas en interne
                compterWagons_d(monTrain);
                break;

            case 13:
                calculerCapacite_d(monTrain);
                break;

            case 14:
                libererTrain_d(monTrain);
                break;

            case 15:
                printf("\nLiberation de la memoire et fermeture du programme...\n");
                libererTrain_d(monTrain);
                free(monTrain);
                printf("A bientot !\n");
                return 0;

            default:
                printf("\nErreur : Choix invalide. Veuillez reessayer.\n");
        }
    }
    return 0;
}

