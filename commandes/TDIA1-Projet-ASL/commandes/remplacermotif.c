#include <stdio.h>
#include <stdlib.h>

#define SUCCES 0
#define ECHEC 1

int remplacerMotif(const char *nomFichier, const char *motifRecherche, const char *motifRemplacement) {
    // Construction de la commande sed
    char commande[1024];
    sprintf(commande, "sed -i 's/%s/%s/g' %s", motifRecherche, motifRemplacement, nomFichier);

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

