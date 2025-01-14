#include "../include/itineraires.h"
#include "../include/transport.h"  

// Variables globales
Lg lignes[max];         // Tableau des lignes
int nb_lignes = 0;      // Nombre de lignes
const char *fichier_etat = "Etat.csv"; // Fichier pour enregistrer les itinéraires

    void rechercher_itineraire() {
    char depart[max], arrivee[max];

    // Demande à l'utilisateur de saisir les arrêts de départ et d'arrivée
    printf("Entrer l'arrêt de départ : ");
    scanf("%s", depart);
    printf("Entrer l'arrêt d'arrivée : ");
    scanf("%s", arrivee);

    // Vérification si les arrêts existent dans le réseau
    int arret_depart_trouve = 0, arret_arrivee_trouve = 0;
    for (int i = 0; i < nb_lignes; i++) {
        for (int j = 0; j < lignes[i].nb_arrets; j++) {
            if (strcmp(lignes[i].arret[j].Nom_arret, depart) == 0) arret_depart_trouve = 1;
            if (strcmp(lignes[i].arret[j].Nom_arret, arrivee) == 0) arret_arrivee_trouve = 1;
        }
    }

    if (!arret_depart_trouve || !arret_arrivee_trouve) {
        printf("L'un des arrêts n'existe pas dans le réseau.\n");
        return;
    }

    // Parcourt toutes les lignes pour trouver un itinéraire direct
    for (int i = 0; i < nb_lignes; i++) {
        int pos_depart = -1, pos_arrivee = -1;

        // Recherche les positions des arrêts de départ et d'arrivée dans la ligne actuelle
        for (int j = 0; j < lignes[i].nb_arrets; j++) {
            if (strcmp(lignes[i].arret[j].Nom_arret, depart) == 0) pos_depart = j;
            if (strcmp(lignes[i].arret[j].Nom_arret, arrivee) == 0) pos_arrivee = j;
        }

        // Vérifie si les arrêts sont sur la même ligne et dans le bon ordre
        if (pos_depart != -1 && pos_arrivee != -1 && pos_depart < pos_arrivee) {
            // Affiche l'itinéraire trouvé
            printf("Itinéraire trouvé sur la ligne %s : ", lignes[i].Nom_ligne);
            for (int k = pos_depart; k <= pos_arrivee; k++) {
                printf("%s -> ", lignes[i].arret[k].Nom_arret);
            }
            printf("Fin\n");

            // Enregistre l'itinéraire dans le fichier `Etat.csv`
            FILE *trajet = fopen(fichier_etat, "a");
            if (trajet) {
                fprintf(trajet, "Itinéraire : Ligne %s de %s à %s\n", lignes[i].Nom_ligne, depart, arrivee);
                fclose(trajet);
            }
            return; // Arrête la recherche une fois l'itinéraire trouvé
        }
    }

    // Si aucun itinéraire direct n'a été trouvé
    printf("Aucun itinéraire direct trouvé entre %s et %s.\n", depart, arrivee);
}

        void rechercher_itineraire_correspondances() {
    char depart[max], arrivee[max];

    // Demande à l'utilisateur de saisir les arrêts de départ et d'arrivée
    printf("Entrer l'arrêt de départ : ");
    scanf("%s", depart);
    printf("Entrer l'arrêt d'arrivée : ");
    scanf("%s", arrivee);

    // Vérifie si les arrêts existent dans le réseau
    int arret_depart_trouve = 0, arret_arrivee_trouve = 0;
    for (int i = 0; i < nb_lignes; i++) {
        for (int j = 0; j < lignes[i].nb_arrets; j++) {
            if (strcmp(lignes[i].arret[j].Nom_arret, depart) == 0) arret_depart_trouve = 1;
            if (strcmp(lignes[i].arret[j].Nom_arret, arrivee) == 0) arret_arrivee_trouve = 1;
        }
    }

    if (!arret_depart_trouve || !arret_arrivee_trouve) {
        printf("L'un des arrêts n'existe pas dans le réseau.\n");
        return;
    }

    // Recherche d'un itinéraire avec correspondance
    for (int i = 0; i < nb_lignes; i++) {
        int pos_depart = -1;

        // Recherche de l'arrêt de départ sur `Ligne_1`
        for (int j = 0; j < lignes[i].nb_arrets; j++) {
            if (strcmp(lignes[i].arret[j].Nom_arret, depart) == 0) {
                pos_depart = j;
                break;
            }
        }

        if (pos_depart != -1) { // Si le départ est trouvé
            // Parcourt des autres lignes pour trouver une correspondance et l'arrivée
            for (int k = 0; k < nb_lignes; k++) {
                if (i == k) continue; // Ignore la même ligne

                int pos_inter = -1, pos_arrivee = -1;

                // Recherche d'une correspondance sur `Ligne_2`
                for (int m = 0; m < lignes[k].nb_arrets; m++) {
                    for (int n = 0; n < lignes[i].nb_arrets; n++) {
                        if (strcmp(lignes[i].arret[n].Nom_arret, lignes[k].arret[m].Nom_arret) == 0) {
                            pos_inter = m;
                            break;
                        }
                    }
                    if (strcmp(lignes[k].arret[m].Nom_arret, arrivee) == 0) {
                        pos_arrivee = m;
                    }
                }

                // Vérifie si une correspondance et l'arrivée sont valides
                if (pos_inter != -1 && pos_arrivee != -1 && pos_inter < pos_arrivee) {
                    printf("Itinéraire trouvé avec correspondance :\n");
                    printf("Ligne %s : %s -> %s\n", lignes[i].Nom_ligne, depart, lignes[i].arret[pos_inter].Nom_arret);
                    printf("Ligne %s : %s -> %s\n", lignes[k].Nom_ligne, lignes[k].arret[pos_inter].Nom_arret, arrivee);

                    // Sauvegarde de l'itinéraire dans le fichier `Etat.csv`
                    FILE *trajet = fopen(fichier_etat, "a");
                    if (trajet) {
                        fprintf(trajet, "Itinéraire avec correspondance : Ligne %s (%s -> %s), Ligne %s (%s -> %s)\n",
                                lignes[i].Nom_ligne, depart, lignes[i].arret[pos_inter].Nom_arret,
                                lignes[k].Nom_ligne, lignes[k].arret[pos_inter].Nom_arret, arrivee);
                        fclose(trajet);
                    }
                    return; // Arrête la recherche après avoir trouvé un itinéraire
                }
            }
        }
    }

    // Si aucun itinéraire avec correspondance n'a été trouvé
    printf("Aucun itinéraire avec correspondance trouvé entre %s et %s.\n", depart, arrivee);
}


