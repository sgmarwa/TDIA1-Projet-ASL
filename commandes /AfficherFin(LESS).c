#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 20  // Nombre de lignes par page

void display_file(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(ECHEC);
    }

    const char *filename = argv[1];

    display_file(filename);

    return SUCCESS;
}

void display_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(ECHEC);
    }

    int c;
    int line_count = 0;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);

        if (c == '\n') {
            line_count++;

            if (line_count == PAGE_SIZE) {
                printf("-- Appuyez sur Entrée pour continuer --\n");
                getchar();  // Attend l'appui sur la touche Entrée
                line_count = 0;
            }
        }
    }

    fclose(file);
}
