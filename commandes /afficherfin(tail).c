#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "loggin.h"
#include "usr.h"
char utilisateur[50]
FILE *f3 = fopen("connecteur.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);

int main(int argc, char *argv[]) {
    // Vérifier le nombre d'arguments
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <nom fichier> [-n]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Déclarer et initialiser les variables
    const char *nom_fichier = argv[1];
    FILE *f = fopen(nom_fichier, "r");

    // Vérifier si le fichier a pu être ouvert
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
         logMessage2("DEBUG","utilisation du commande <lister>: fichier non trouvé",utilisateur );
        return EXIT_FAILURE;
    }

    char ligne[1000];
    int nombre_lignes = 5;  // Valeur par défaut

    // Si un argument optionnel est fourni
    if (argc == 3) {
        if (argv[2][0] == '-' && isdigit(argv[2][1])) {
            nombre_lignes = atoi(argv[2] + 1);
        } else {
            printf("Erreur : Argument invalide pour le nombre de lignes.\n");
            printf("Usage: %s <nom fichier> [-n]\n", argv[0]);
            fclose(f);
            return EXIT_FAILURE;
        }
    }

    // Compter le nombre total de lignes dans le fichier
    int cmpt = 0;
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        cmpt++;
    }

    // Réinitialiser le curseur au début du fichier
    fseek(f, 0, SEEK_SET);

    // Afficher les dernières lignes en fonction du nombre spécifié
    int i = 0;
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        i++;
        if (i > cmpt - nombre_lignes) {
            logMessage2("DEBUG","utilisation du commande <lister>",utilisateur );
            printf("%s", ligne);
        }
    }

    // Fermer le fichier après utilisation
    fclose(f);
    fclose(f3);
    return 0;
}
