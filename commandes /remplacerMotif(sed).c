#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCES 0
#define ECHEC 1
#define TAILLE_BUFFER 1024

int remplacerMotif(const char *nomFichier, const char *motifRecherche, const char *motifRemplacement) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return ECHEC;
    }

    char ligne[TAILLE_BUFFER];
    char *nouvelleLigne;
    size_t tailleMotifRecherche = strlen(motifRecherche);
    size_t tailleMotifRemplacement = strlen(motifRemplacement);

    FILE *fichierTemporaire = tmpfile();  // Créer un fichier temporaire

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *occurrence = ligne;
        while ((occurrence = strstr(occurrence, motifRecherche)) != NULL) {
            fwrite(ligne, 1, occurrence - ligne, fichierTemporaire);
            fwrite(motifRemplacement, 1, tailleMotifRemplacement, fichierTemporaire);
            occurrence += tailleMotifRecherche;
            ligne = occurrence;
        }
        fwrite(ligne, 1, strlen(ligne), fichierTemporaire);
    }

    fseek(fichierTemporaire, 0, SEEK_SET);
    fseek(fichier, 0, SEEK_SET);

    while (fgets(ligne, sizeof(ligne), fichierTemporaire) != NULL) {
        fputs(ligne, fichier);
    }

    fclose(fichier);
    fclose(fichierTemporaire);

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
