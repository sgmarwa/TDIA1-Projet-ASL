#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *source_file, *destination_file;
    char ch;

    // Vérifie le nombre d'arguments
    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    // Ouvre le fichier source en lecture
    source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
        printf("Impossible d'ouvrir le fichier source '%s'\n", argv[1]);
        return 1;
    }

    // Ouvre le fichier destination en écriture
    destination_file = fopen(argv[2], "w");
    if (destination_file == NULL) {
        printf("Impossible d'ouvrir le fichier destination '%s'\n", argv[2]);
        fclose(source_file);
        return 1;
    }

    // Copie le contenu du fichier source vers le fichier destination
    while ((ch = fgetc(source_file)) != EOF) {
        fputc(ch, destination_file);
    }

    // Ferme les fichiers
    fclose(source_file);
    fclose(destination_file);

    printf("Le fichier '%s' a été copié vers '%s'\n", argv[1], argv[2]);
    return 0;
}
