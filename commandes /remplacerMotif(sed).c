#include <stdio.h>
#include <stdlib.h>
#include "loggin.h"
#include "usr.h"
#define SUCCES 0
#define ECHEC 1
char utilisateur[50];
FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3);
int remplacerMotif(const char *nomFichier, const char *motifRecherche, const char *motifRemplacement) {
    // Construction de la commande sed
    char commande[1024];
    sprintf(commande, "sed -i 's/%s/%s/g' %s", motifRecherche, motifRemplacement, nomFichier);
    logMessage2("DEBUG","utilisation du commande <remplacerMotif>",utilisateur);
    // Exécution de la commande
    int resultat = system(commande);

    if (resultat == -1) {
        perror("Erreur lors de l'exécution de la commande sed");
        return ECHEC;
    }

    return SUCCES;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "La formule correcte est : %s <fichier> <motifRecherche> <motifRemplacement>\n", argv[0]);
        exit(ECHEC);
    }

    const char *nomFichier = argv[1];
    const char *motifRecherche = argv[2];
    const char *motifRemplacement = argv[3];

    int resultat = remplacerMotif(nomFichier, motifRecherche, motifRemplacement);

    if (resultat == SUCCES) {
        printf("Remplacement réussi dans le fichier %s.\n", nomFichier);
    } else {
        fprintf(stderr, "Échec du remplacement dans le fichier %s.\n", nomFichier);
    }

    return resultat;
}
