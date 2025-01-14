#include "../include/transport.h"
#include "../include/itineraires.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 500
int main(){
int choix;
 do {
        printf("\033[4;34m_____ Gestion des lignes de transport _____\033[0m\n");// in blue colors
        printf("1. Ajouter une ligne\n");
        printf("2. Affichage des lignes disponibles \n");
        printf("3. Modifier une ligne\n");
        printf("4. Supprimer une ligne\n");
        printf("5. Rechercher un itineraire sans correspandances\n");
        printf("6. Recherche avancee d'un itineraire avec correspandances\n");
        printf("7.Quitter le programme \n");
        printf(" Entrez votre choix  : ");
        scanf("%d", &choix);
        

        switch (choix) {
            case 1:
                Ajouter_Ligne();
                break;
            case 2:
                Affichage_Lignes();
                break;   
            case 3:
                Modifier_Ligne();
                break;
            case 4: 
                Supprimer_Ligne();
                break;
            case 5:
                rechercher_itineraire();
            case 6: 
                rechercher_itineraire_correspondances();    
            case 7:
                printf("Au revoir ");
                break;    
             default :
                printf("choix invalid  ");
        }
 }   while (choix != 7); // afficher le menu si le choix est invalide
 
    return 0; 
}
