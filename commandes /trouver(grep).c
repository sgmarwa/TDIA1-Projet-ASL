#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "loggin.h"
#include "usr.h"
#define ECHEC 1
#define SUCES 0
char utilisateur[50];
FILE *f3 = fopen("connecteur.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur),f3);
void trouver(const char *pattern, const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "La formule correcte est : %s <pattern> <filename>\n", argv[0]);
        exit(ECHEC);
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    trouver(pattern, filename);

    return SUCES;
}

void trouver(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        logMessage2("DEBUG","utilisation du commande <trouver>: fichier non trouvé",utilisateur );
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
 logMessage2("DEBUG","utilisation du commande <trouver>", utilisateur);
    fclose(file);
    fclose(f3);
}
