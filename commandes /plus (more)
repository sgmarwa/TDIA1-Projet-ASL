#include <stdio.h>

#define PAGE_SIZE 20 // Nombre de lignes par page

void mymore(FILE *fp) {
    int line_count = 0;
    char ch;

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);

        if (ch == '\n') {
            line_count++;
        }

        // Si le nombre de lignes atteint la taille de la page, attend l'entrée de l'utilisateur pour continuer
        if (line_count == PAGE_SIZE) {
            printf("\n--More--");
            getchar(); // Attend une entrée de l'utilisateur pour continuer
            line_count = 0; // Réinitialise le compteur de lignes pour la prochaine page
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *file;

    if (argc != 2) {
        printf("Usage: %s file_name\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    mymore(file);

    fclose(file);

    return 0;
}
