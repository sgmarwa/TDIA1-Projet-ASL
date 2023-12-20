#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void trouver(const char *pattern, const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "la formule correcte est : %s <pattern> <filename>\n", argv[0]);
        exit(ECHEC);
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    trouver(pattern, filename);

    return SUCCES;
}

void trouver(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(ECHEC);
    }

    regex_t regex;
    int ret;

    // Compilation du motif en une expression régulière
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char error_message[100];
        regerror(ret, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Erreur lors de la compilation du motif : %s\n", error_message);
        exit(ECHEC);
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Recherche du motif dans chaque ligne du fichier
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }

    // Libération de la mémoire utilisée par l'expression régulière
    regfree(&regex);

    fclose(file);
}