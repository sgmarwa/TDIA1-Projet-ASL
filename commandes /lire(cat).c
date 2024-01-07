#include <stdio.h>
#include <stdlib.h>
#include "loggin.h"
#include "usr.h"
char utilisateur[50];
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        return EXIT_FAILURE;
    }
 /*   FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3); */

    const char *nom_fichier = argv[1];
    FILE *fichier = fopen(nom_fichier, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
    //    logMessage2("DEBUG","utilisation du commande <lire>: fichier non trouvé",utilisateur);
        return EXIT_FAILURE;
    }

    int caractere;
    while ((caractere = fgetc(fichier)) != EOF) {
        putchar(caractere);
    }
//logMessage2("DEBUG","utilisation du commande <lire>",utilisateur );
    fclose(fichier);
    return EXIT_SUCCESS;
}
