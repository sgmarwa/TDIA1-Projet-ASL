#include <stdio.h>
#include <unistd.h>
#include "loggin.h"
#include "usr.h"
int main() {
    char utilisateur[50];
FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3);
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Position: %s\n", cwd);
        logMessage2("DEBUG","utilisation du commande <position>",utilisateur);
    } else {
        perror("Erreur lors de la récupération du répertoire actuel");
        return 1;
    }

    return 0;
}
