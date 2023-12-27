#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include "loggin.h"
#include "usr.h"
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE  "\033[34m"
#define COLOR_GREEN "\033[32m"
char utilisateur[50];
FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3);

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        logMessage2("DEBUG","utilisation du commande <lister>: fichier non trouvé",utilisateur );
        perror("Impossible d'ouvrir le répertoire");
        return;
    }

    struct dirent *entry;
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int count = 0;
    int max_length = 0;

    // Calculer la longueur maximale des noms de fichiers
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.' && strlen(entry->d_name) > max_length) {
            max_length = strlen(entry->d_name);
        }
    }

    rewinddir(dir);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            char file_type = '-';
            if (entry->d_type == DT_DIR) {
                file_type = 'd';
            }

            // Calculer le nombre d'espaces nécessaires pour aligner les colonnes
            int spaces = max_length - strlen(entry->d_name) + 5;  // 5 espaces pour la séparation

            // Calculer le nombre d'éléments pouvant tenir dans une ligne
            int elements_per_line = w.ws_col / (max_length + 5);

            printf("%s%s%s%s%*s", COLOR_BLUE, file_type == 'd' ? COLOR_GREEN : "", entry->d_name, COLOR_RESET, spaces, "");

            count++;

            // Aller à la ligne après chaque nombre défini d'entrées par ligne
            if (count == elements_per_line) {
                printf("\n");
                count = 0;
            }
        }
    }

    // Aller à la ligne à la fin si la dernière ligne n'est pas complète
    if (count != 0) {
        printf("\n");
    }
logMessage1("DEBUG","utilisation du commande <lister>",utilisateur);
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    char chemin[PATH_MAX];
    strcpy(chemin, argv[1]);

    // Ajouter un '/' à la fin du chemin si ce n'est pas déjà le cas
    if (chemin[strlen(chemin) - 1] != '/') {
        strcat(chemin, "/");
    }

    list_directory(chemin);

    return 0;
}
