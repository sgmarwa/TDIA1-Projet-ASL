#include <stdio.h>
#include <stdlib.h>
#include "loggin.h"
#include "usr.h"
#define TAILLE_PAGE 20

#define ECHEC 1
#define SUCES 0
char utilisateur[50];
FILE *f3 = fopen("connecteur.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);

void affichepage(const char *nom_fichier);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "La formule correcte est : %s <nom_fichier>\n", argv[0]);
        exit(ECHEC);
    }

    const char *nom_fichier = argv[1];

    affichepage(nom_fichier);

    return SUCES;
}

void affichepage(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        logMessage2("DEBUG","utilisation du commande <afficherpage>: fichier non trouvé",utilisateur);
        perror("Erreur lors de l'ouverture du fichier");
        exit(ECHEC);
    }

    int c;
    int nb_lignes = 0;
    while ((c = fgetc(fichier)) != EOF) {
        putchar(c);

        if (c == '\n') {
            nb_lignes++;

            if (nb_lignes == TAILLE_PAGE) {
                printf("-- Appuyez sur Entrée pour continuer, 'q' pour quitter --\n");

                int saisie = getchar();

                if (saisie == 'q') {
                    break;
                } else if (saisie == '\n') {
                    nb_lignes = 0;
                }
            }
        }
    }
logMessage2("DEBUG","utilisation du commande <afficherpage>",utilisateur);
    fclose(fichier);
    fclose(f3);
}

