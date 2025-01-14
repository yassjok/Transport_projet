#include "../include/transport.h"
#include "../include/itineraires.h"
#include "transport.h"
#include "itineraires.h"

    void Ajouter_Ligne(){
        Lg Lignes;
        int nbr_arret ,i ;
      FILE *trajet = fopen("Lignes_gestion.csv","a+");
      if (trajet==NULL){
        printf("Ereur dans l'ouverture du fichier de gestion des lignes 1");
        exit(1);
      }
printf ("Entrez le nom de la nouvelle ligne:");
gets(Lignes.Nom_ligne);
while (getchar() != '\n');  // Vide le tampon
printf(" \n Entrez le nombre d'arrets pour cette Ligne: ");
scanf("%d",&nbr_arret);
for ( i=0 ; i<nbr_arret ;i++){ // boucle pour les arrets
    printf("Entrez le nom d'arret %d \n",i);
    while (getchar() != '\n'); 
    gets(Lignes.arret[i+1].Nom_arret); // Vide le tampon
    printf("Entree l'heure de passage \n");
   gets(Lignes.arret[i+1].heure_passage);
    fputs(Lignes.Nom_ligne,trajet);
    fputs(Lignes.arret[i+1].Nom_arret,trajet); // stockage dans le fichier 
    fputs(Lignes.arret[i+1].heure_passage,trajet);
}

      fclose(trajet);
    }

 
void Affichage_Lignes(){
    int ligne_choix;  // Variable pour stocker le choix de l'utilisateur
    FILE *trajet = fopen("Lignes_gestion.csv", "a+");
    if (trajet == NULL) {
        printf("Erreur dans l'ouverture du fichier de gestion des lignes\n");
        exit(1);  
    }
    do {
        printf("Voulez-vous afficher toutes les lignes (1) ou bien une ligne spécifiée (2) ? Entrez 1 ou 2 :\n");
        scanf("%d", &ligne_choix);
    } while (ligne_choix != 1 && ligne_choix != 2);  // Vérification de la validité de la saisie

    //  Affichage de toutes les lignes
    if (ligne_choix == 1) {
        Lg ligne;                 // Structure pour stocker une ligne
        char ligne_txt[256];      //  lire chaque ligne du fichier

        // Lecture du fichier ligne par ligne
        while (fgets(ligne_txt, sizeof(ligne_txt), trajet)) {
            // Extraction du nom de la ligne et du nombre d'arrêts
            sscanf(ligne_txt, "%s,%d", ligne.Nom_ligne, &ligne.nb_arrets);

            printf("Ligne: %s\n", ligne.Nom_ligne);
            printf("Arrêts:\n");

            // Lecture et affichage des arrêts de la ligne
            for (int i = 0; i < ligne.nb_arrets; i++) {
                fgets(ligne_txt, sizeof(ligne_txt), trajet);  // Lire l'arrêt suivant
                sscanf(ligne_txt, "%[^,],%s", ligne.arret[i].Nom_arret, ligne.arret[i].heure_passage);
                printf("  %s - %s\n", ligne.arret[i].Nom_arret, ligne.arret[i].heure_passage);
            }
            printf("\n");
        }

    //  Affichage d'une ligne spécifique 
    } else {
        char nv_ligne[max];  // Variable pour stocker le nom de la ligne à rechercher

        // Demander le nom de la ligne à afficher
        printf("Entrez le nom de la ligne à afficher : ");
        scanf("%s", nv_ligne);

        rewind(trajet);  // Remettre le pointeur au début du fichier

        Lg ligne;               // Structure pour stocker les données de la ligne
        char ligne_txt[256];    // Buffer pour la lecture du fichier
        int ligne_trouvee = 0;  // Indicateur pour vérifier si la ligne existe

        // Recherche de la ligne spécifiée
        while (fgets(ligne_txt, sizeof(ligne_txt), trajet)) {
            // Extraction du nom de la ligne et du nombre d'arrêts
            sscanf(ligne_txt, "%[^,],%d", ligne.Nom_ligne, &ligne.nb_arrets);

            // Vérification si la ligne correspond à celle saisie par l'utilisateur
            if (strcmp(ligne.Nom_ligne, nv_ligne) == 0) {
                ligne_trouvee = 1;  // Ligne trouvée
                printf("Ligne: %s\n", ligne.Nom_ligne);
                printf("Arrets:\n");

                // Lecture et affichage des arrêts de la ligne trouvée
                for (int i = 0; i < ligne.nb_arrets; i++) {
                    fgets(ligne_txt, sizeof(ligne_txt), trajet);
                    sscanf(ligne_txt, "%[^,],%s", ligne.arret[i].Nom_arret, ligne.arret[i].heure_passage);
                    printf("  %s - %s\n", ligne.arret[i].Nom_arret, ligne.arret[i].heure_passage);
                }
                printf("\n");
                break;  // Arrêt de la recherche après avoir trouvé la ligne
            }
        }

        // Si la ligne n'a pas été trouvée
        if (!ligne_trouvee) {
            printf("La ligne %s n'a pas été trouvee.\n", nv_ligne);
        }
    }

    fclose(trajet);  // Fermeture du fichier
}

 
    ///
    void Modifier_Ligne(){ // Fonction Pour modifier une ligne
         
         FILE *trajet = fopen("Lignes_gestion.csv", "a+");
    if (trajet == NULL) {
        printf("Erreur dans l'ouverture du fichier de gestion des lignes\n");
        exit(1);  
    }
         Lg Lignes;
         int i;
         char line_mod[max];
         char ligne_txt[max]; // variable pour la ligne a modifier
         printf("Entrer le nom de la ligne a modifier");
         gets(line_mod);
char new_nom[max];
int new_nbr; // new nbre d'arret
char new_arret[max];
char new_heure [max];

           // Recherche de la ligne spécifiée
        while (fgets(ligne_txt, sizeof(ligne_txt), trajet)) {
            // Extraction du nom de la ligne et du nombre d'arrêts
            sscanf(ligne_txt, "%[^,],%d", Lignes.Nom_ligne, &Lignes.nb_arrets);

            // Vérification si la ligne correspond à celle saisie par l'utilisateur
            if (strcmp(Lignes.Nom_ligne, line_mod) == 0) {
printf("Entrez le nouvau nom de la ligne:");
gets(new_nom);
while (getchar() != '\n');  // Vide le tampon
printf(" \nEntrez les nouvau nombres d'arrets :");
scanf("%d",&new_nbr);
while (getchar() != '\n');  // Vide le tampon
for ( i=0 ; i<new_nbr ;i++){ // boucle pour les arrets
    printf("\n Entrez le nom d'arret nouvau %d \n",i);
    gets(new_arret);
    while (getchar() != '\n');  // Vide le tampon
    printf("\nEntree la nouvelle heure de passage \n");
   gets(new_heure);
    fputs(new_nom,trajet); 
    fprintf(trajet,"Les arreets avec les les horriares de passage \n");
    fputs(new_arret,trajet); // stockage dans le fichier 
    fputs(new_heure,trajet);
}
    }
        }
    }

    void Supprimer_Ligne() // Fonction pour supprimer une ligne 
    {
     FILE *trajet = fopen("Lignes_gestion.csv", "a+");
    if (trajet == NULL) {
        printf("Erreur dans l'ouverture du fichier de gestion des lignes\n");
        exit(1);  
    }    
// Ouvrir un fichier temporaire en écriture
    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        exit(1); 
       
    }

    Lg Lignes ;
    char Ligne_rmv[max];
    char ligne_txt[max];
    int ligne_trouvee = 0;
    int ignorer_ligne = 0;

    printf("Entrz le nom de ligne a supprimer :");
    gets(Ligne_rmv);
    // Recherche de la ligne spécifiée
        while (fgets(ligne_txt, sizeof(ligne_txt), trajet)) {
            // Extraction du nom de la ligne et du nombre d'arrêts
            sscanf(ligne_txt, "%[^,],%d", Lignes.Nom_ligne, &Lignes.nb_arrets);

            // Vérification si la ligne correspond à celle saisie par l'utilisateur
            if (strcmp(Lignes.Nom_ligne, Ligne_rmv) == 0) {
                     ligne_trouvee = 1;
                        ignorer_ligne = 1;  // Activer le mode suppression
            continue;           // Passer à la ligne suivante
            }
    
    
        // Ignorer les arrêts de la ligne à supprimer
        if (ignorer_ligne) {
            if (strcmp(ligne_txt, "\n") == 0) {
                ignorer_ligne = 0;  // Fin des arrêts, on reprend la copie
            }
            continue;  // Ne pas copier cette ligne
        }

        // Copier les lignes restantes dans le fichier temporaire
        fputs(ligne_txt, temp);
    }

    fclose(temp);
    fclose(trajet);
    
    
    // Remplacer le fichier original par le fichier temporaire
    if (ligne_trouvee) {
        remove("Lignes_gestion.csv");           // Supprimer l'ancien fichier
        rename("temp.csv", "Lignes_gestion.csv");  // Renommer le fichier temporaire
        printf("La ligne '%s' a été supprimée avec succès.\n", Lignes.Nom_ligne);
    } else {
        remove("temp.csv");  // Nettoyer le fichier temporaire
        printf("La ligne '%s' n'a pas été trouvée.\n", Lignes.Nom_ligne);
    }
    
    }


